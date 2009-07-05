#include "common.h"
#include "unfold.h"
#include "order.h"
#include "test.h"
#include <string.h>

/*****************************************************************************/

/**
 * The worklist of possible extensions is organized as a priority heap
 * using an array (of pointers). The array is extended in steps of size
 * PE_ALLOC_STEP as needed.
 */

#define PE_ALLOC_STEP 1024
/// the priority array
hist_t **pe_queue;
/// current capacity
int	pe_qsize,
/// maximum capacity
	pe_qalloc;

/**
 * Initializes the queue
 */
void pe_init ()
{
	pe_qsize = 0;
	pe_qalloc = PE_ALLOC_STEP;
	pe_queue = MYmalloc(pe_qalloc * sizeof(hist_t*));
}

/**
 * Adds the possible extension (tr,pe_conds) to the priority queue.
 */
void pe_insert (hist_t *h)
{
	hist_t *qu_new = h;
	int index = ++pe_qsize;

	if (pe_qsize >= pe_qalloc)
	{
		pe_qalloc += PE_ALLOC_STEP;
		pe_queue = MYrealloc(pe_queue, pe_qalloc * sizeof(hist_t*));
	}

	// insert new element at the end, then move upwards as needed
	for (; index > 1; index /= 2)
	{
		if (pe_compare(qu_new, pe_queue[index/2]) > 0) break;
		pe_queue[index] = pe_queue[index/2]; // move parent downwards
	}
	pe_queue[index] = qu_new;
}

/**
 * Remove the minimal event from the queue and restore order.
 */
hist_t *pe_pop ()
{
	hist_t *first = pe_queue[1];
	hist_t *last;
	int index = 1, newindex;

	if (!pe_qsize) return NULL;

	last = pe_queue[pe_qsize--];
	for (;;)	// sift last element downwards
	{
		if (index > pe_qsize / 2) break;
		// compare "last" and children of index
		if (index*2 < pe_qsize
			&& pe_compare(last,pe_queue[index*2+1]) > 0)
		{
			if (pe_compare(pe_queue[index*2],pe_queue[index*2+1])>0)
				newindex = index*2 + 1;
			else
				newindex = index*2;
		}
		else if (pe_compare(last,pe_queue[index*2]) > 0)
			newindex = index * 2;
		else
			break;
		pe_queue[index] = pe_queue[newindex];	// move child upwards
		index = newindex;
	}
	pe_queue[index] = last;
	return first;
}

/**
 * @arg e an event
 * @return im(e* U _e_) subset of S
 */
array_t *im_post_context(event_t *e)
{
	int len = e->postset->len + e->readarcs->len;
	array_t *places = array_new(len);
	int i = 0;
	for (i = 0; i < e->postset->count; i++)
		array_append(places, ((cond_t *)
			array_get(e->postset, i))->origin);
	for (i = 0; i < e->readarcs->count; i++)
		array_append(places, ((cond_t *)
			array_get(e->readarcs, i))->origin);
	return places;
}

/**
 * Computes the postset of a set of places S
 * @arg S the unordered set of places
 * @return the ordered set of transitions (no duplicates)
 */
array_t *place_postset(array_t *S)
{
	array_t *T = array_new(0);
	int i;
	for (i = 0; i < S->count; i++) {
		nodelist_t *post = ((place_t *)array_get(S, i))->postset;
		while (post != NULL) {
			array_insert_ordered(T, post->node);
			post = post->next;
		}
		nodelist_t *cont = ((place_t *)array_get(S, i))->readarcs;
		while (cont != NULL) {
			array_insert_ordered(T, cont->node);
			cont = cont->next;
		}
	}
	array_sort(T);
#ifdef __DEBUG__
	for (i=0; i < T->count-1; i++) {
		g_assert(array_get(T, i) < array_get(T, i+1));
	}
#endif
	return T;
}

/**
 * Test whether \f$\,^\bullet tr \cup \underline{tr}\f$ in co and returns the
 * set of conditions that need to
 * be pairwise concurrent to create a new history for an event e;
 * @arg tr the transition enabled after the insertion of H
 * @arg co the set of concurrent conditions for all conditions in
 * 	\f$e_H^\bullet \cup \underline{e_H}\f$
 * @arg n_causes a pointer to an integer which will contain the number of causal
 * 	conditions present in the returned co-structure
 * @return the set of conditions if they all have an image in the preset, NULL
 * 	otherwise. Note that this is a subset of co and shares memory with it:
 * 	do not destroy it's histories!
 * 	Note that this structure is not ordered on conditions!
 */
co_t *test_trans(trans_t *tr, co_t *co)
{
	int len = tr->preset_size + tr->readarc_size, i, j;
#ifdef __DEBUG__
	check_co(co);
#endif
	nodelist_t *pre = tr->preset;
	nodelist_t *ra = tr->readarcs;
	co_t *S = co_array_new(len);

	for (j = 0; pre != NULL; (pre = pre->next), j++)
		for (i = 0; i < co->len; i++)
			if (co->conds[i].cond->origin == pre->node)
				co_insert_co_cond(S + j, co->conds + i);

	for (j = 0; ra != NULL; (ra = ra->next), j++)
		for (i = 0; i < co->len; i++)
			if (co->conds[i].cond->origin == ra->node)
				co_insert_co_cond(S + j + tr->preset_size,
						  co->conds + i);
	// Check if every place has at list one condition:
	for (i = 0; i < len; i++) {
		if (S[i].len == 0) {
			co_array_finalize(S, len);
			return NULL;
		}
#ifdef __DEBUG__
		else {
			check_co(S + i);
		}
#endif
	}
	// Return the array of co structures:
	return S;
}

/**
 * Check if a predecessor is concurrent to all the already inserted predecessors
 * @return true if it is concurrent to all preds[i], i = 0..j-1; false otherwise
 */
UNFbool pairwise_concurrent(pred_t *preds, int j)
{
	UNFbool cont = UNF_TRUE;
	pred_t *pred = preds + j;
	--j;
	co_t *co_common =
		g_hash_table_lookup(pred->cond->pre_ev->co, pred->hist);
	co_t *co_private =
		g_hash_table_lookup(pred->cond->co_private, pred->hist);
	while (cont && j>0) {
		// TODO: binary search to accelerate this process
		int k, l;
		UNFbool found = UNF_FALSE;
		for (k = 0; !found && k < co_common->len; k++) {
			if (co_common->conds[k].cond == preds[j].cond) {
				for (l = 0; !found &&
					l < co_common->conds[k].hists_len; l++)
					if (co_common->conds[k].hists[l] ==
					    preds[j].hist)
						found = UNF_TRUE;
			}
		}
		for (k = 0; !found && k < co_private->len; k++) {
			if (co_private->conds[k].cond == preds[j].cond) {
				for (l = 0; !found &&
					l < co_private->conds[k].hists_len; l++)
					if (co_private->conds[k].hists[l] ==
					    preds[j].hist)
						found = UNF_TRUE;
			}
		}
		if (!found) cont = UNF_FALSE;
		--j;
	}
	return cont;
}

/**
 * Tests if an history is chosen causal for a condition
 * @arg hist the history
 * @arg cond the condition
 * @return the result of the test
 */
UNFbool hist_c(hist_t *hist, cond_t *cond)
{
	if (cond->pre_ev == hist->e)
		return UNF_TRUE;
	return UNF_FALSE;
}

void pred_sort(pred_t *pred, int pred_n)
{
	int i, j;
	for (i=1; i<pred_n; i++) {
		j = i-1;
		pred_t tmp;
		memcpy(&tmp, pred + i, sizeof(pred_t));
		while (j>=0 && pred[j].cond > tmp.cond) {
			memcpy(pred + j + 1, pred + j, sizeof(pred_t));
			--j;
		}
		memcpy(pred + j + 1, &tmp, sizeof(pred_t));
	}
#ifdef __DEBUG__
	for (i = 0; i < pred_n-1; i++) {
		g_assert(pred[i].cond < pred[i+1].cond);
	}
#endif
}

void set_cond(array_t *preset, array_t *readarcs, int i, cond_t *co)
{
	if (i < preset->count) {
		array_get(preset, i) = co;
	} else {
		array_get(readarcs, i-preset->count) = co;
	}
}

void find_subset_rec(trans_t *t, co_t *S, pred_t *preds, array_t *ps, array_t *ra,
		     int s_i, int pred_i, int i, int j, int added);
void find_pred_rec(trans_t *t, co_t *S, pred_t *preds, array_t *ps, array_t *ra,
		   int s_i, int pred_i)
{
	int i;
	if (s_i < t->preset_size) {
		// Only for the preset: find subset of read histories
		for (i = 0; i < S[s_i].len; i++) {
			find_subset_rec(t, S, preds, ps, ra, s_i, pred_i, i,
					(S[s_i].conds + i)->hists_len-1, 0);
		}
	}

	if (s_i < t->preset_size + t->readarc_size) {
		// Preset and readarcs: select a causal history and go on
		int j;
		SET_FLAG(preds[pred_i].flags, HIST_C);
		for (i = 0; i < S[s_i].len; i++) {
			co_cond_t *cond = S[s_i].conds + i;
			preds[pred_i].cond = cond->cond;
			set_cond(ps, ra, s_i, cond->cond);
			// Chose a causal history for the current condition,
			// check if it is pairwise concurrent with all other
			// histories; if so continue computing the predecessors
			// with this history.
			for (j = 0; j < cond->hists_len; j++) {
				preds[pred_i].hist = cond->hists[j];
				if (hist_c(cond->hists[j], cond->cond) &&
				    pairwise_concurrent(preds, pred_i))
					find_pred_rec(t, S, preds, ps, ra,
						      s_i+1, pred_i+1);
			}
		}
	} else {
		// Predecessor list complete: add history to pe
		// Find if there is already the event in the unfolding whose
		// image in the original net is t; if not, create it.
		array_t *events = preds->cond->postset;
		event_t *e = NULL;
		i = 0;
		while (i < events->count &&
		       ((event_t*)array_get(events, i))->origin != t)
			i++;
		if (i >= events->count) {
			// Event not found in the unfolding, try to find it
			// in the list of possible extensions

			// TODO

			// Event not found, create it.
			e = nc_event_new(t, array_copy(ps), array_copy(ra));
		} else
			e = array_get(events, i);

		hist_t *hist = (hist_t *)MYmalloc(sizeof(hist_t));
		hist->e = e;
		hist->flags = 0;
		hist->pred_n = t->preset_size + t->readarc_size;
		hist->pred = MYmalloc(sizeof(pred_t) * hist->pred_n);
		memcpy(hist->pred, preds, sizeof(pred_t) * hist->pred_n);
		pred_sort(hist->pred, hist->pred_n);
		size_mark(hist);
		// Add the newly created history to the list of possible
		// extensions
		pe_insert(hist);
	}
}

/**
 * Recursive function; computes all possible subsets of concurrent read
 * histories
 */
void find_subset_rec(trans_t *t, co_t *S, pred_t *preds, array_t *ps, array_t *ra,
		     int s_i, int pred_i, int i, int j, int added)
{
	co_cond_t *cond = S[s_i].conds + i;
	if (j>=0) {
		if (!hist_c(cond->hists[j], cond->cond)) {
			// predecessors without cond->hists[j]
			find_subset_rec(t, S, preds, ps, ra, s_i, pred_i, i,
					j-1, added);

			// predecessors with cond->hists[j]
			preds[pred_i].cond = cond->cond;
			SET_FLAG(preds[pred_i].flags, HIST_R);
			preds[pred_i].hist = cond->hists[j];
			if (pairwise_concurrent(preds, pred_i)) {
				find_subset_rec(t, S, preds, ps, ra, s_i,
						     pred_i+1, i, j-1, added+1);
			}
		} else {
			// Causal history, ignore it
			find_subset_rec(t, S, preds, ps, ra, s_i, pred_i, i,
					j-1, added);
		}
	} else if (added > 0) {
		set_cond(ps, ra, s_i, cond->cond);
		find_pred_rec(t, S, preds, ps, ra, s_i+1, pred_i);
	}
}

/**
 * Find all possible pairwise concurrent sets of predecessors for a new history;
 * once one set is found add it to possible extensions
 */
void find_pred(trans_t *t, co_t *S)
{
	int i, j, pred_size = 0;
	for (i = 0; i < t->preset_size; i++) {
		int max_h = 0;
		for (j = 0; j < S[i].len; j++)
			if (S[i].conds->hists_len > max_h)
				max_h = S[i].conds->hists_len;
		pred_size += max_h;
	}
	pred_size += t->readarc_size;
	array_t *ps = array_new(t->preset_size);
	ps->count = ps->len;
	array_t *ra = array_new(t->readarc_size);
	ra->count = ra->len;
	pred_t *preds = MYmalloc(sizeof(pred_t) * pred_size);
	find_pred_rec(t, S, preds, ps, ra, 0, 0);
	free(preds);
	array_delete(ps);
	array_delete(ra);
}

/**
 * Find the new possible extensions created by the addition of h.
 */
void pe (hist_t *h)
{
	array_t *S = im_post_context(h->e);
	// T gets the list of transitions enabled by places in the postset
	// and context of e.
	array_t *T = place_postset(S);
	array_delete(S);

	co_t *co = (co_t *)g_hash_table_lookup(h->e->co, h);
	int i;
	for (i = 0; i<T->count; i++) {
		trans_t *tr = array_get(T, i);
		check_co(co);
		co_t *S = test_trans(tr, co);
		if (S != NULL) {
			// *t U _t_ is a subset of im(co)
			find_pred(tr, S);
			co_array_finalize(S, tr->preset_size +
					  tr->readarc_size);
		}
	}
}
