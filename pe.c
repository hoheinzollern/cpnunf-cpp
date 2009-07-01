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
	array_t *T = array_new(1);
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
co_t *test_trans(trans_t *tr, co_t *co, int *n_causes)
{
	if (tr!=NULL) {
		check_co(co);
		nodelist_t *pre = tr->preset;
		nodelist_t *context = tr->readarcs;
		UNFbool good = UNF_TRUE;
		co_t *pair_co = co_new(tr->preset_size + tr->readarc_size);
		int count = 0;
		while (pre != NULL && good == UNF_TRUE) {
			// TODO: optimize this part: sets of places in the
			// original net should be kept ordered.
			int i;
			// try to find the place of tr's preset in the
			// co-conditions'image
			for (i=0; i<co->len &&
			     co->conds[i].cond->origin!=(place_t *)pre->node;
			     i++);
			if (i>=co->len)
				good = UNF_FALSE;
			else {
				// add the found conditions
				pair_co->conds[count].cond = co->conds[i].cond;
				pair_co->conds[count].hists = co->conds[i].hists;
				pair_co->conds[count].hists_len =
						co->conds[i].hists_len;
				count++;
			}
			pre = pre->next;
		}
		*n_causes = count;
		while (context != NULL && good == UNF_TRUE
		       && count < pair_co->len) {
			// TODO: optimize this part: sets of places in the
			// original net should be kept ordered.
			int i;
			// try to find the place of tr's context in the
			// co-conditions'image
			for (i=0; i<co->len &&
			     co->conds[i].cond->origin!=(place_t *)context->node;
			     i++);
			if (i>=co->len)
				good = UNF_FALSE;
			else {
				// add the found conditions
				pair_co->conds[count].cond = co->conds[i].cond;
				pair_co->conds[count].hists = co->conds[i].hists;
				pair_co->conds[count].hists_len =
						co->conds[i].hists_len;
			}
			count++;
			context = context->next;
		}
		pair_co->len = count;
		check_co(pair_co);
		if (good) {
			return pair_co;
		} else {
			// don't call co_finalize as pair_co shares histories
			// with co
			free(pair_co->conds);
			free(pair_co);
			return NULL;
		}
	} else
		return NULL;
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
UNFbool hist_causal_for(hist_t *hist, cond_t *cond)
{
	if (cond->pre_ev == hist->e)
		return UNF_TRUE;
	return UNF_FALSE;
}

void find_pred(trans_t *t, co_t *B, int n_causes, pred_t *preds, int depth,
	       int *pred_n);
/**
 * Recursive function; computes all possible subsets of concurrent read
 * histories
 */
void read_hist_subset_rec(trans_t *t, co_t *B, int n_causes, pred_t *preds,
			  int depth, int *pred_n, int i)
{
	if (i>=0) {
		co_cond_t *cond = B->conds + depth;
		if (!hist_causal_for(cond->hists[i], cond->cond)) {
			// predecessors without cond->hists[i]
			read_hist_subset_rec(t, B, n_causes, preds, depth,
					     pred_n, i-1);

			// predecessors with cond->hists[i]
			preds[*pred_n].cond = cond->cond;
			SET_FLAG(preds[*pred_n].flags, HIST_R);
			if (pairwise_concurrent(preds, *pred_n)) {
				++*pred_n;
				read_hist_subset_rec(t, B, n_causes, preds,
						     depth, pred_n, i-1);
				--*pred_n;
			}
		} else {
			// Causal history, ignore it
			read_hist_subset_rec(t, B, n_causes, preds, depth,
					     pred_n, i-1);
		}
	} else {
		find_pred(t, B, n_causes, preds, depth+1, pred_n);
	}
}

void pred_sort(pred_t *pred, int pred_n)
{
	int i, j;
	for (i=1; i<pred_n; i++) {
		j = i-1;
		pred_t tmp = pred[i];
		memcpy(&tmp, pred + i, sizeof(pred_t));
		while (j>=0 && pred[j].cond > tmp.cond) {
			memcpy(pred + j + 1, pred + j, sizeof(pred_t));
			--j;
		}
		memcpy(pred + j + 1, &tmp, sizeof(pred_t));
		// TODO: check if structure assignment makes a valid copy of
		// the entire structure.
	}
}

/**
 * Find all possible pairwise concurrent sets of predecessors for a new history;
 * once one set is found add it to possible extensions
 */
void find_pred(trans_t *t, co_t *B, int n_causes, pred_t *preds, int depth,
	       int *pred_n)
{
	if (depth == 0) {
		pred_n = (int *)MYmalloc(sizeof(int));
		*pred_n = 0;
		int size = 0;
		int i;
		for (i = 0; i < B->len; i++)
			size += B->conds[i].hists_len;
		// Allocate the maximum possible length for a predecessors list
		preds = (pred_t *)MYmalloc(sizeof(pred_t) * size);
	}
	if (depth < B->len) {
		int i;
		co_cond_t *cond = B->conds + depth;
		preds[*pred_n].cond = cond->cond;
		if (depth < n_causes) {
			SET_FLAG(preds[*pred_n].flags, HIST_C);
			// Chose a causal history for the current condition,
			// check if it is pairwise concurrent with all other
			// histories; if so continue computing the predecessors
			// with this history.
			for (i = 0; i<cond->hists_len; i++)
			     if (hist_causal_for(cond->hists[i],
						 preds[*pred_n].cond)
				 && pairwise_concurrent(preds, *pred_n)) {
				preds[*pred_n].hist = cond->hists[i];
				// all chosen predecessors are pairwise
				// concurrent, go on.
				++(*pred_n);
				find_pred(t, B, n_causes, preds, depth + 1,
					  pred_n);
				--(*pred_n);
			}
			//			OR
			// Chose each concurrent subset of read histories and do
			// the same thing.
			for (i = 0; i<cond->hists_len; i++)
			     if (!hist_causal_for(cond->hists[i], cond->cond)
					&& pairwise_concurrent(preds, *pred_n))
				     {
				// chose this history Hi as a pivot and then
				// a subset of H' s.t. H' < Hi and H' is readH
				preds[*pred_n].hist = cond->hists[i];
				++(*pred_n);
				read_hist_subset_rec(t, B, n_causes, preds,
					depth, pred_n, i-1);
				--(*pred_n);
			}
		} else {
			SET_FLAG(preds[*pred_n].flags, HIST_R);
			// Chose a read history for the current condition, check
			// if it is pairwise concurrent with all other
			// histories; if so continue computing the predecessors
			// with this history.
			for (i = 0; i<cond->hists_len; i++) {
				preds[*pred_n].hist = cond->hists[i];
				if (hist_causal_for(cond->hists[i],
						    preds[*pred_n].cond)
					&& pairwise_concurrent(preds, *pred_n))
					{
					// all chosen predecessors are pairwise
					// concurrent, go on.
					++(*pred_n);
					find_pred(t, B, n_causes, preds,
						  depth + 1, pred_n);
					--(*pred_n);
				}
			}
		}
	} else {
		// we found a set of concurrent predecessors for H, add it to
		// pe; find if there is already the event in the unfolding whose
		// image in the original net is t; if not, create it.
		array_t *events = NULL;
		if (n_causes>0)
			events = preds->cond->postset;
		else
			events = preds->cond->readarcs;
		int j = 0;
		while (j<events->count &&
		       ((event_t*)array_get(events, j))->origin != t)
			j++;
		event_t *e;
		if (j>=events->count) {
			// Event not found, create it.
			// Create array for preset and readarcs
			array_t *preset = array_new(n_causes);
			for (j = 0; j<n_causes; j++)
				array_get(preset, j) = B->conds[j].cond;
			array_t *readarcs = array_new(B->len - n_causes);
			for (j = n_causes; j<B->len; j++)
				array_get(readarcs, j-n_causes) =
						B->conds[j].cond;
			// Create the event
			e = nc_event_new(t, preset, readarcs);
		} else
			e = (event_t*)array_get(events, j);

		hist_t *hist = (hist_t *)MYmalloc(sizeof(hist_t));
		hist->e = e;
		hist->flags = 0;
		hist->pred = MYmalloc(sizeof(pred_t) * *pred_n);
		hist->pred_n = *pred_n;
		memcpy(hist->pred, preds, sizeof(pred_t) * *pred_n);
		pred_sort(hist->pred, hist->pred_n);
		size_mark(hist);
		// Add the newly created history to the list of possible
		// extensions
		pe_insert(hist);
	}
	if (depth == 0) {
		free(pred_n);
		free(preds);
	}
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
		int n_causes;
		check_co(co);
		co_t *B = test_trans(array_get(T, i), co, &n_causes);
		if (B != NULL) {
			// *t U _t_ is a subset of im(co)
			check_co(B);
			find_pred(array_get(T, i), B, n_causes, NULL, 0, NULL);
			free(B->conds);
			free(B);
		}
	}
}
