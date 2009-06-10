#include <string.h>

#include "common.h"
#include "netconv.h"
#include "pe.h"
#include "marking.h"
#include "unfold.h"

net_t *net;	/* stores the net	*/
unf_t *unf;	/* stores the unfolding */

int exitcode = 0;
int conditions_size, events_size, ce_alloc_step;
int ev_mark;
cond_t  **conditions;			/* condition queue in marking_of   */
event_t **events;			/* event queue in pe_conflict etc. */
trans_t *stoptr = NULL;			/* transition in -T switch         */

nodelist_t *cutoff_list, *corr_list;	/* cut-off list, corresponding events */

/**
 * creates a new empty co structure
 */
co_t *co_new(int size)
{
	co_t *co = MYmalloc(sizeof(co_t));
	co->len = size;
	co->conds = MYmalloc(sizeof(co_cond_t) * size);
	co_cond_t *co_cond;
	for (co_cond = co->conds; co_cond<co->conds+size; ++co_cond) {
		co_cond->cond = NULL;
		co_cond->hists = NULL;
	}
	return co;
}

/**
 * creates a copy of the co-structure
 */
co_t *co_copy(co_t *orig)
{
	co_t *co = co_new(orig->len);
	co_cond_t *co_cond, *orig_cond = orig->conds;
	for (co_cond = co->conds; co_cond < co->conds+co->len;
		    ++co_cond, ++orig_cond) {
		co_cond->cond = orig_cond->cond;
		co_cond->hists_len = orig_cond->hists_len;
		co_cond->hists = MYmalloc(sizeof(hist_t *) *
					  co_cond->hists_len);
		memcpy(co_cond->hists, orig_cond->hists,
		       sizeof(hist_t *) * co_cond->hists_len);
	}
	return co;
}

/**
 * Frees the memory used for a coarray structure
 */
void co_finalize(co_t *co)
{
	co_cond_t *last = co->conds + co->len,
		*co_cond = co->conds;
	while (co_cond < last) {
		free(co_cond->hists);
		++co_cond;
	}
	free(co->conds);
	free(co);
}

/**
 * Computes the intersection of a and b and stores it in b
 */
void hist_intersect(hist_t **a, int len_a, hist_t ***b, int *len_b)
{
	int size_b = *len_b;
	*len_b = 0;
	hist_t	**last_a = a + len_a,
		**last_b = *b + *len_b,
		**cur_b = *b;
	
	// intersects the history arrays
	while (a < last_a && *b < last_b) {
		if (*a == **b) {
			cur_b = a;
			a++; b++; cur_b++; (*len_b)++;
		} else if (*a < **b) a++;
		else b++;
	}
	while (cur_b < last_b) {
		*cur_b = NULL;
		cur_b++;
	}
	// TODO: strip the length of the array to the used size
}

/**
 * intersects two array of concurrent conditions for two pairs <a,Ha>, <b,Hb>
 * and stores it in b
 */
void co_intersect(co_t *a, co_t *b)
{
	int len_c = 0;
	co_cond_t *cond_a = a->conds, *lastcond_a = a->conds + a->len,
		*cond_b = b->conds, *lastcond_b = b->conds + b->len,
		*cond_c = cond_b;
	
	while (cond_a < lastcond_a && cond_b < lastcond_b) {
		if (cond_a->cond == cond_b->cond) {
			// a == b is a condition present in both co-arrays
			cond_c->cond = cond_a->cond;
			if (cond_b != cond_c)
				free(cond_c->hists);
			
			// so find the intersection of both histories
			hist_intersect(cond_a->hists, cond_a->hists_len,
				       &(cond_b->hists), &(cond_b->hists_len));
			cond_c->hists_len = cond_b->hists_len;
			cond_c->hists = cond_b->hists;
			cond_b->hists = NULL;
			cond_a++; cond_b++; cond_c++; len_c++;
		} else if (cond_a->cond < cond_b->cond) {
			cond_a++;
		} else {
			free(cond_b->hists);
			cond_b++;
		}
	}
	while (cond_c < lastcond_b) {
		cond_c->cond = NULL;
		cond_c->hists_len = 0;
		if (cond_c->hists != NULL)
			free(cond_c->hists);
		cond_c->hists = NULL;
		cond_c++;
	}
	b->len = len_c;
	// TODO: strip the length of the array to the used size
}

/**
 * takes a co structure and eliminates the preset of a given event
 * note that preset and the co structure are both ordered on conditions
 */
void co_drop_preset(co_t *co, event_t *ev)
{
	co_cond_t *cond1 = co->conds, *cond2 = co->conds,
		*lastcond = co->conds + co->len;
	array_t *pre = ev->preset;
	int i = 0;
	
	while (i < pre->len && cond2 < lastcond) {
		if (g_array_index(pre, cond_t *, i) == cond2->cond) {
			free(cond2->hists);
			cond2->hists = NULL;
			cond2++; i++;
			co->len--;
		} else if (cond1 != cond2) {
			*cond1 = *cond2;
			cond1++; cond2++;
		} else {
			cond1++; cond2++;
		}
	}
	while (cond1 < lastcond) {
		cond1->cond = NULL;
		cond1->hists_len = 0;
		cond1->hists = NULL;
	}
}

/**
 * Copies a co-condition from src to dst
 */
void co_cond_copy(co_cond_t *dst, co_cond_t *src)
{
	dst->cond = src->cond;
	dst->hists_len = src->hists_len;
	dst->hists = MYmalloc(sizeof(hist_t *) * dst->hists_len);
	memcpy(dst->hists, src->hists, sizeof(hist_t *) * dst->hists_len);
}

/**
 * Creates the union of h1 and h2 and stores it in h3 (allocating a new
 * memory area for this).
 */
void hist_union(hist_t **h1, int len_h1, hist_t **h2, int len_h2,
		hist_t ***h3, int *len_h3)
{
	*h3 = MYmalloc(sizeof(hist_t *) * (len_h1 + len_h2));
	int i=0, j=0, k=0;
	while (i < len_h1 && j < len_h2) {
		if (h1[i] < h2[j]) {
			(*h3)[k] = h1[i];
			k++; i++;
		} else if (h1[i] == h2[j]) {
			(*h3)[k] = h1[i];
			k++; i++; j++;
		} else {
			(*h3)[k] = h2[j];
			k++; j++;
		}
	}
	while (i < len_h1) {
		(*h3)[k] = h1[i];
		k++; i++;
	}
	while (j < len_h2) {
		(*h3)[k] = h2[j];
		k++; j++;
	}
	*len_h3 = k;
	// TODO: strip the size of the union
}

/**
 * Computes the union of two co relations
 */
co_t *co_union(co_t *a, co_t *b)
{
	co_t *c = co_new(a->len + b->len);
	c->len = 0;
	
	co_cond_t *cond_a = a->conds, *cond_b = b->conds, *cond_c = c->conds;
	co_cond_t *last_a = a->conds + a->len,
		  *last_b = b->conds + b->len;
	while (cond_a < last_a && cond_b < last_b) {
		if (cond_a->cond < cond_b->cond) {
			co_cond_copy(cond_a, cond_c);
			cond_a++;
		} else if (cond_a->cond == cond_b->cond) {
			cond_c->cond = cond_a->cond;
			hist_union(cond_a->hists, cond_a->hists_len,
				   cond_b->hists, cond_b->hists_len,
				   &(cond_c->hists), &(cond_c->hists_len));
		} else {
			co_cond_copy(cond_b, cond_c);
			cond_b++;
		}
		c->len++;
		cond_c++;
	}
	while (cond_a < last_a) {
		co_cond_copy(cond_a, cond_c);
		cond_a++;
		c->len++;
		cond_c++;
	}
	while (cond_b < last_b) {
		co_cond_copy(cond_b, cond_c);
		cond_b++;
		c->len++;
		cond_c++;
	}
	
	return c;
}

/**
 * Inserts a pair <b, H> in a co_relation
 * @arg co the co relation
 * @arg cond the condition part of the pair
 * @arg hist the history part of the pair
 */
void co_insert(co_t *co, cond_t *cond, hist_t *hist)
{
	co_cond_t *conds = co->conds;
	int i = 0, len = co->len;
	// Navy search of the place; TODO: consider binary search
	while (i < len && conds[i].cond < cond)
		i++;
	if (i < len && conds[i].cond == cond) {
		// cond is already found in the co_structure, so 
		// just insert the history
		int j = 0;
		while (j < conds[i].hists_len && hist < conds[i].hists[j])
			j++;
		if (j >= conds[i].hists_len || hist != conds[i].hists[j]) {
			// The history is not found, so add it to the array
			hist_t **hists = MYmalloc(conds[i].hists_len+1);
			memcpy(hists, conds[i].hists, sizeof(hist_t *) * j);
			memcpy(hists + j + 1, conds[i].hists + j,
				sizeof(hist_t *) * (conds[i].hists_len-j+1));
			hists[j] = hist;
			free(conds[i].hists);
			conds[i].hists = hists;
			conds[i].hists_len++;
		}
	} else {
		// cond is not found, insert it in the co_structure
		conds = MYmalloc(sizeof(co_cond_t *) * (len+1) );
		memcpy(conds, co->conds, sizeof(co_cond_t *) * i);
		memcpy(conds + i + 1, co->conds + i,
			sizeof(co_cond_t *) * (len-i+1));
		conds[i].cond = cond;
		conds[i].hists_len = 1;
		conds[i].hists = MYmalloc(sizeof(hist_t *));
		conds[i].hists[0] = hist;
	}
}

/**
 * Given an enriched event e, returns the pairs <b, H> in the postset of e
 * as a co structure.
 */
co_t *co_postset_e(hist_t *hist)
{
	array_t *post = hist->e->postset;
	co_t *co = co_new(post->len);
	co_cond_t *cond = co->conds, *last_cond = co->conds + co->len;
	int i = 0;
	while (cond < last_cond) {
		cond->cond = g_array_index(post, cond_t *, i);
		cond->hists_len = 1;
		cond->hists = MYmalloc(sizeof(hist_t *));
		*(cond->hists) = hist;
		cond++; i++;
	}
}

/**
 * Computes the co-relation given an enriched event. See theory at section
 * "Keeping co and qco-relations" for details.
 * Also updates the reverse side of the relation for each condition inserted.
 * @arg hist the enriched event just inserted
 * @return the co-relation for the event
 */
co_t *co_relation(hist_t *hist)
{
	pred_t *pred = hist->pred, *last_pred = hist->pred + hist->pred_n;
	co_t *tmp = NULL;
	while (pred < last_pred) {
		if (HAS_FLAG(pred->flags, HIST_C)) {
			co_t *co_b = co_union(
				(co_t*)g_hash_table_lookup(
					pred->cond->co_private, pred->hist),
				(co_t*)g_hash_table_lookup(
					pred->hist->e->co, pred->hist)
			);
			if (tmp) {
				co_intersect(co_b, tmp);
				co_finalize(co_b);
			} else
				tmp = co_b;
		} else if (HAS_FLAG(pred->flags, HIST_R)) {
			co_t *co_b = co_union(
				g_hash_table_lookup(pred->cond->co_private,
					pred->hist),
				g_hash_table_lookup(pred->hist->e->co,
					pred->hist)
					     );
			co_t *co_qco_b = co_union(co_b,
				g_hash_table_lookup(pred->hist->e->qco,
					pred->hist)
						 );
			co_finalize(co_b);
			if (tmp) {
				co_intersect(co_qco_b, tmp);
				co_finalize(co_qco_b);
			} else
				tmp = co_qco_b;
		}
		pred++;
	}
	co_drop_preset(tmp, hist->e);
	co_t *co_post = co_postset_e(hist);
	co_t *result = co_union(tmp, co_post);
	co_finalize(tmp);
	co_finalize(co_post);
	
	// Adds the reverse side of the relation:
	array_t *post_e = hist->e->postset;
	co_cond_t *co = result->conds, *last_co = result->conds + result->len;
	for (; co < last_co; co++) {
		hist_t **h = co->hists, **last_h = co->hists + co->hists_len;
		for (; h < last_h; h++) {
			co_t *co_b1 = g_hash_table_lookup(co->cond->co_private,
							   *h);
			if (co_b1 == NULL) {
				co_b1 = co_new(0);
				g_hash_table_insert(co->cond->co_private, *h,
						     co_b1);
			}
			int i = 0;
			for (; i < post_e->len; i++) {
				cond_t *b = g_array_index(post_e, cond_t *, i);
				co_insert(co_b1, b, hist);
			}
		}
	}
	
	return result;
}

/**
 * Computes the qco-relation given an enriched event.
 */
co_t *qco_relation(hist_t *hist)
{
	pred_t *pred = hist->pred, *last_pred = hist->pred + hist->pred_n;
	// Store in tmp the union of qco in hist
	co_t *tmp = NULL;
	while (pred < last_pred) {
		co_t *qco_b = g_hash_table_lookup(
				pred->hist->e->qco, pred->hist);
		if (tmp != NULL) {
			qco_b = co_union(tmp, qco_b);
			co_finalize(tmp);
		}
		tmp = qco_b;
		pred++;
	}
	pred = hist->pred;
	while (pred < last_pred) {
		co_t *co_b = co_union(
			g_hash_table_lookup(pred->hist->e->co, pred->hist),
			g_hash_table_lookup(pred->cond->co_private, pred->hist)
		);
		co_t *co_qco_b = co_union(co_b,
			g_hash_table_lookup(pred->hist->e->qco, pred->hist));
		co_finalize(co_b);
		co_intersect(co_qco_b, tmp);
	}
	co_drop_preset(tmp, hist->e);
	return tmp;
}

/**
 * Adds an history to the unfolding, then finds new possible estensions
 */
void add_history(hist_t *hist)
{
	event_t *e = hist->e;
	// Finds if an event is in the unfolding:
	if (!g_hash_table_lookup(unf->events, hist->e))
	{
		nc_add_event(e);
	}
	g_hash_table_insert(e->hist, hist, hist);
	
	// Computes co and qco relations
	co_t *co_rel = co_relation(hist),
	    *qco_rel = qco_relation(hist);
	
	g_hash_table_insert(hist->e->co, hist, co_rel);
	g_hash_table_insert(hist->e->qco, hist, qco_rel);
	
	// Adds the marking of hist to the unfolding
	g_hash_table_insert(unf->markings, hist->parikh, hist);
}

/*****************************************************************************/

/**
 * Checks if h is a local cutoff
 */
UNFbool cutoff(hist_t *h1)
{
	hist_t *h2 = g_hash_table_lookup(unf->markings, h1->parikh);
	return (h2 != NULL && pe_compare(h1, h2) > 0);
}

/**
 * Computes the unfolding of the net
 */
void unfold ()
{
	unf = nc_create_unfolding();
	
	// root event and initial marking:
	event_t *ev = unf->root = (event_t *)MYmalloc(sizeof(event_t));
	ev->num = -1;
	
	ev->origin = NULL;
	ev->preset = array_new(0);
	ev->readarcs = array_new(0);
	
	// Adds the initial marking for the root event
	unf->m0 = marking_initial();
	array_t *post = ev->postset = array_new(1);
	nodelist_t *ps = unf->m0;
	while (ps) {
		cond_t *cond = nc_cond_new(ps->node, ev);
		array_append(post, cond);
		ps = ps->next;
	}
	array_sort(post);
	
	ev->co = g_hash_table_new(NULL, NULL);
	ev->qco = g_hash_table_new(NULL, NULL);
	ev->hist = g_hash_table_new(NULL, NULL);
	
	// empty history for root event
	hist_t *h0 = (hist_t *)MYmalloc(sizeof(hist_t));
	g_hash_table_insert(ev->hist, h0, h0);
	h0->e = ev;
	h0->flags = 0;
	h0->pred = NULL;
	h0->pred_n = 0;
	size_mark(h0);
	// initialize co-conditions:
	co_t *co = co_new(ev->postset->len);
	int i;
	for (i=0; i<ev->postset->len; i++) {
		co->conds[i].cond = (cond_t *)array_get(ev->postset, i);
		co->conds[i].hists = (hist_t **)MYmalloc(sizeof(hist_t *));
		co->conds[i].hists_len = 1;
		co->conds[i].hists[0] = h0;
	}
	g_hash_table_insert(ev->co, h0, co);
	
	// Unfolding:
	hist_t *h = NULL;
	while ((h = pe_pop()) != NULL) {
		if (!cutoff(h)) {
			add_history(h);
			pe(h);
		} else
			nodelist_push(&cutoff_list, h);
	} 
}
