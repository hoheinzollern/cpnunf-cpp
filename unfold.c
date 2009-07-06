#include <string.h>

#include "common.h"
#include "netconv.h"
#include "pe.h"
#include "marking.h"
#include "unfold.h"
#include "test.h"
#include <stdio.h>
#include "output.h"

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
	if (size > 0) {
		co->conds = MYmalloc(sizeof(co_cond_t) * size);
		co_cond_t *co_cond;
		for (co_cond = co->conds; co_cond<co->conds+size; ++co_cond) {
			co_cond->cond = NULL;
			co_cond->hists = NULL;
		}
	} else {
		co->conds = NULL;
	}
	return co;
}

/**
 * creates an array of empty co-structures
 */
co_t *co_array_new(int n)
{
	co_t *co = MYmalloc(sizeof(co_t) * n);
	int i;
	for (i = 0; i < n; i++) {
		co[i].len = 0;
		co[i].conds = NULL;
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
 * Frees the memory used for a co-structure
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
 * Frees the memory used for a co array structure
 */
void co_array_finalize(co_t *co, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		co_cond_t *last = co[i].conds + co[i].len,
			*co_cond = co[i].conds;
		while (co_cond < last) {
			free(co_cond->hists);
			++co_cond;
		}
		free(co[i].conds);
	}
	free(co);
}

void co_fprint(FILE *stream, co_t *co)
{
	int i, j;
	for (i = 0; i < co->len; i++) {
		fprintf(stream, "b%d (%s): ", co->conds[i].cond->num,
		       co->conds[i].cond->origin->name);
		for (j = 0; j < co->conds[i].hists_len; j++) {
			print_ll_history(stream, co->conds[i].hists[j]);
		}
	}
}

/**
 * Computes the intersection of a and b and stores it in b
 */
void hist_intersect(hist_t **a, int len_a, hist_t ***b, int *len_b)
{
	hist_t	**last_a = a + len_a,
		**last_b = *b + *len_b,
		**cur_a = a, **cur_b = *b, **cur_c = *b;
	int len_c = 0;
	
	// intersects the history arrays
	while (cur_a < last_a && cur_b < last_b) {
		if (*cur_a == *cur_b) {
			*cur_c = *cur_a;
			++cur_a; ++cur_b; ++cur_c; ++len_c;
		} else if (*cur_a < *cur_b) ++cur_a;
		else ++cur_b;
	}
	while (cur_c < last_b) {
		*cur_c = NULL;
		++cur_c;
	}
	*len_b = len_c;
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
			
			// so find the intersection of both histories
			hist_intersect(cond_a->hists, cond_a->hists_len,
				       &(cond_b->hists), &(cond_b->hists_len));
			// if there are histories in the intersection copy them
			if (cond_b->hists_len > 0) {
				cond_c->hists_len = cond_b->hists_len;
				cond_c->hists = cond_b->hists;
				cond_a++; cond_b++; cond_c++; len_c++;
			} else {
				free(cond_b->hists);
				cond_a++;
				cond_b++;
			}
		} else if (cond_a->cond < cond_b->cond) {
			cond_a++;
		} else {
			free(cond_b->hists);
			cond_b++;
		}
	}
	while (cond_b < lastcond_b) {
		cond_b->cond = NULL;
		cond_b->hists_len = 0;
		if (cond_b->hists != NULL)
			free(cond_c->hists);
		cond_b->hists = NULL;
		cond_b++;
	}
	b->len = len_c;
	// TODO: strip the length of the array to the used size
#ifdef __DEBUG__
	check_co(b);
#endif
}

/**
 * takes a co structure and eliminates the preset of a given event
 * note that preset and the co structure are both ordered on conditions
 */
void co_drop_preset(co_t *co, event_t *ev)
{
	array_t *pre = ev->preset;
	int i = 0, cond = 0;
	
	while (i < pre->count && cond < co->len) {
		if ((cond_t*)array_get(pre, i) == co->conds[cond].cond) {
			free(co->conds[cond].hists);
			memmove(co->conds + cond, co->conds + cond + 1,
				sizeof(co_cond_t)*(co->len - cond - 1));
			cond++; i++;
			co->len--;
		} else {
			cond++;
		}
	}
#ifdef __DEBUG__
	for (i = 0; i < co->len; i++)
		g_assert(co->conds[i].hists!=NULL);
#endif
}

/**
 * Copies a co-condition from src to dst
 */
void co_cond_copy(co_cond_t *dst, co_cond_t *src)
{
#ifdef __DEBUG__
	check_co_cond(src);
#endif
	dst->cond = src->cond;
	dst->hists_len = src->hists_len;
#ifdef __DEBUG__
	g_assert(src->hists_len > 0);
#endif
	dst->hists = MYmalloc(sizeof(hist_t *) * dst->hists_len);
	memcpy(dst->hists, src->hists, sizeof(hist_t *) * dst->hists_len);
#ifdef __DEBUG__
	check_co_cond(src);
#endif
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


#ifdef __DEBUG__
	// Check if union has all necessary histories
	i = 0; j = 0; k = 0;
	while (i < len_h1 || j < len_h2) {
		g_assert((i < len_h1 && h1[i] == (*h3)[k]) ||
			 (j < len_h2 && h2[j] == (*h3)[k]));
		if (i < len_h1 && h1[i] == (*h3)[k])
			i++;
		if (j < len_h2 && h2[j] == (*h3)[k])
			j++;
		k++;
	}
#endif
}

/**
 * Computes the union of two co relations
 */
co_t *co_union(co_t *a, co_t *b)
{
#ifdef __DEBUG__
	check_co(a);
	check_co(b);
#endif
	co_t *c = co_new(a->len + b->len);
	c->len = 0;
	
	co_cond_t *cond_a = a->conds, *cond_b = b->conds, *cond_c = c->conds;
	co_cond_t *last_a = a->conds + a->len,
		  *last_b = b->conds + b->len;
	while (cond_a < last_a && cond_b < last_b) {
#ifdef __DEBUG__
		g_assert(a->len != 0);
		g_assert(b->len != 0);
#endif
		if (cond_a->cond < cond_b->cond) {
			co_cond_copy(cond_c, cond_a);
			cond_a++;
		} else if (cond_a->cond == cond_b->cond) {
			cond_c->cond = cond_a->cond;
			hist_union(cond_a->hists, cond_a->hists_len,
				   cond_b->hists, cond_b->hists_len,
				   &(cond_c->hists), &(cond_c->hists_len));
			cond_a++; cond_b++;
		} else {
			co_cond_copy(cond_c, cond_b);
			cond_b++;
		}
		c->len++;
		cond_c++;
#ifdef __DEBUG__
		check_co(c);
#endif
	}
	while (cond_a < last_a) {
		co_cond_copy(cond_c, cond_a);
		cond_a++;
		c->len++;
		cond_c++;
#ifdef __DEBUG__
		check_co(c);
#endif
	}
	while (cond_b < last_b) {
		co_cond_copy(cond_c, cond_b);
		cond_b++;
		c->len++;
		cond_c++;
#ifdef __DEBUG__
		check_co(c);
#endif
	}
	
#ifdef __DEBUG__
	// Check if union has all necessary conditions
	cond_a = a->conds; cond_b = b->conds; cond_c = c->conds;
	while (cond_a < last_a || cond_b < last_b) {
		g_assert((cond_a < last_a && cond_a->cond == cond_c->cond) ||
			 (cond_b < last_b && cond_b->cond == cond_c->cond));
		if (cond_a < last_a && cond_a->cond == cond_c->cond)
			cond_a++;
		if (cond_b < last_b && cond_b->cond == cond_c->cond)
			cond_b++;
		cond_c++;
	}
#endif
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
	// Naive search of the place; TODO: consider binary search
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
		conds = MYmalloc(sizeof(co_cond_t) * (len+1) );
		if (len > 0) {
			memcpy(conds, co->conds, sizeof(co_cond_t) * i);
			memcpy(conds + i + 1, co->conds + i,
				sizeof(co_cond_t) * (len-i+1));
		}
		conds[i].cond = cond;
		conds[i].hists_len = 1;
		conds[i].hists = MYmalloc(sizeof(hist_t *));
		conds[i].hists[0] = hist;
	}
}

void co_insert_co_cond(co_t *co, co_cond_t *cond)
{
	co_cond_t *conds = co->conds;
	int i = 0, len = co->len;
	while (i < len && conds[i].cond < cond->cond)
		i++;
	conds = MYmalloc(sizeof(co_cond_t) * (len+1) );
	if (len > 0) {
		memcpy(conds, co->conds, sizeof(co_cond_t) * i);
		memcpy(conds + i + 1, co->conds + i,
			sizeof(co_cond_t) * (len-i));
	}
	conds[i].cond = cond->cond;
	conds[i].hists_len = cond->hists_len;
	conds[i].hists = MYmalloc(sizeof(hist_t *) * cond->hists_len);
	memcpy(conds[i].hists, cond->hists, sizeof(hist_t *) * cond->hists_len);
	co->len = len + 1;
	co->conds = conds;
#ifdef __DEBUG__
	g_assert(co->len > 0);
	g_assert(co->conds != NULL);
	for (i = 0; i < co->len; i++) {
		g_assert(co->conds[i].cond != NULL);
		g_assert(co->conds[i].hists_len > 0);
		g_assert(co->conds[i].hists != NULL);
	}
#endif
}

/**
 * Given an enriched event e, returns the pairs <b, H> in the postset of e
 * as a co structure.
 */
co_t *co_postset_e(hist_t *hist)
{
	array_t *post = hist->e->postset;
	array_t *ra = hist->e->readarcs;
	co_t *co = co_new(post->count + ra->count);
	co_cond_t *cond = co->conds;
	int i = 0, j = 0;
	while (i < post->count || j < ra->count) {
		if (i < post->count && (j >= ra->count ||
		    (array_get(post, i) < array_get(ra, j)))) {
			cond->cond = (cond_t*)array_get(post, i);
			cond->hists_len = 1;
			cond->hists = MYmalloc(sizeof(hist_t *));
			*(cond->hists) = hist;
			cond++; i++;
		} else if (j < ra->count) {
			cond->cond = (cond_t*)array_get(ra, j);
			cond->hists_len = 1;
			cond->hists = MYmalloc(sizeof(hist_t *));
			*(cond->hists) = hist;
			cond++; j++;
		}
	}
	return co;
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
	pred_t *pred = hist->pred;
	co_t *tmp = NULL;
	array_t *ps = hist->e->preset, *ra = hist->e->readarcs;
	int i = 0;
	while (i < ps->count) {
		while (pred->cond < (cond_t*)array_get(ps, i)) pred++;
		while (pred < hist->pred + hist->pred_n
			&& pred->cond == (cond_t*)array_get(ps, i)) {
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
			pred++;
		}
		i++;
	}
	pred = hist->pred;
	i = 0;
	while (i < ra->count) {
		while (pred->cond < (cond_t*)array_get(ra, i)) pred++;
		// For read conditions only a causal history is chosen
		co_t *co_b = co_union(
			g_hash_table_lookup(pred->cond->co_private, pred->hist),
			g_hash_table_lookup(pred->hist->e->co, pred->hist)
				     );
		co_t *co_qco_b = co_union(co_b,
			g_hash_table_lookup(pred->hist->e->qco, pred->hist)
					 );
		co_finalize(co_b);
		if (tmp) {
			co_intersect(co_qco_b, tmp);
			co_finalize(co_qco_b);
		} else
			tmp = co_qco_b;
		pred++;
		i++;
	}
	co_drop_preset(tmp, hist->e);
	co_t *co_post = co_postset_e(hist);
	co_t *result = co_union(tmp, co_post);
#ifdef __DEBUG__
	check_co(tmp);
	check_co(result);
#endif
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

			for (i = 0; i < post_e->count; i++) {
				cond_t *b = (cond_t *)array_get(post_e, i);
				co_insert(co_b1, b, hist);
			}

			for (i = 0; i < ra->count; i++) {
				cond_t *b = (cond_t *)array_get(ra, i);
				co_insert(co_b1, b, hist);
			}
		}
	}
	fprintf(stderr, "co[e%d]:\n", hist->e->num);
	co_fprint(stderr, result);
	fprintf(stderr, "\n\n");
	return result;
}

/**
 * Computes the qco-relation given an enriched event.
 */
co_t *qco_relation(hist_t *hist)
{
	pred_t *pred = hist->pred, *last_pred = hist->pred + hist->pred_n;
	// Store in tmp the union of qco in hist
	co_t *tmp = co_new(0);
	while (pred < last_pred) {
		co_t *qco_b = g_hash_table_lookup(
				pred->hist->e->qco, pred->hist);
		co_t *old_tmp = tmp;
		tmp = co_union(qco_b, tmp);
		co_finalize(old_tmp);
		pred++;
	}
	pred = hist->pred;
	while (pred < last_pred) {
		co_t *co_b = co_union(
			g_hash_table_lookup(pred->hist->e->co, pred->hist),
			g_hash_table_lookup(pred->cond->co_private, pred->hist)
		);
		co_t *qco_b =
			g_hash_table_lookup(pred->hist->e->qco, pred->hist);
		co_t *co_qco_b = co_union(co_b, qco_b);
		co_finalize(co_b);
		co_intersect(co_qco_b, tmp);
		co_finalize(co_qco_b);
		pred++;
	}
	co_drop_preset(tmp, hist->e);
	return tmp;
}

event_t *get_or_create_event(hist_t *hist, UNFbool *created)
{
	// Find if there is already the event in the unfolding whose
	// image in the original net is t; if not, create it.
	array_t *events = hist->pred->cond->postset;
	event_t *e = NULL;
	trans_t *t = hist->e->origin;
	*created = UNF_FALSE;
	int i = 0;
	while (i < events->count &&
	       ((event_t*)array_get(events, i))->origin != t)
		i++;
	if (i >= events->count) {
		// Event not found, create it.
		array_t *ps = array_new(0), *ra = array_new(0);
		pred_t *pred = hist->pred, *last = hist->pred + hist->pred_n;
		for (; pred < last; ++pred) {
			if (HAS_FLAG(pred->flags, PRESET)) {
				array_insert_ordered(ps, pred->cond);
			} else {
				array_insert_ordered(ra, pred->cond);
			}
		}
		e = nc_event_new(t, ps, ra);
		nc_add_event(e);
		*created = UNF_TRUE;
	} else
		e = array_get(events, i);
	return e;
}

/**
 * Adds an history to the unfolding, then finds new possible estensions
 */
void add_history(hist_t *hist)
{
	UNFbool created;
	event_t *e = get_or_create_event(hist, &created);
	free(hist->e);
	hist->e = e;

	// Add history to the unfolding
	g_hash_table_insert(hist->e->hist, hist, hist);
	
	// Computes co and qco relations
	co_t *co_rel = co_relation(hist),
	    *qco_rel = qco_relation(hist);
	
	g_hash_table_insert(hist->e->co, hist, co_rel);
	g_hash_table_insert(hist->e->qco, hist, qco_rel);

#ifdef __DEBUG__
	check_co(co_rel);
	check_co(qco_rel);
	int i;
	for (i = 0; i < net->numpl; i++)
		g_assert(hist->marking[i] == 0 || hist->marking[i] == 1);
#endif

	// Adds the marking of hist to the unfolding
	g_hash_table_insert(unf->markings, hist->marking, hist);
}

/*****************************************************************************/

/**
 * Checks if h is a local cutoff
 */
UNFbool cutoff(hist_t *h1)
{
	hist_t *h2 = g_hash_table_lookup(unf->markings, h1->marking);
	if (h2 != NULL) {
		int i;
		fprintf(stderr, "H[%s]: ", h1->e->origin->name);
		for (i = 0; i < net->numpl; i++)
			fprintf(stderr, "%d", h1->marking[i]);
		fprintf(stderr, "\n");
		fprintf(stderr, "H[e%d (%s)]: ", h2->e->num, h2->e->origin->name);
		for (i = 0; i < net->numpl; i++)
			fprintf(stderr, "%d", h2->marking[i]);
		fprintf(stderr, "\n\n");
		return (pe_compare(h1, h2) > 0);
	} else {
		return UNF_FALSE;
	}
}

/**
 * Computes the unfolding of the net
 */
void unfold ()
{
	unf = nc_create_unfolding();
	parikh_init();
	
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
		g_hash_table_insert(unf->conditions, cond, cond);
		ps = ps->next;
	}
	array_sort(post);
	
	ev->co = g_hash_table_new(NULL, NULL);
	ev->qco = g_hash_table_new(NULL, NULL);
	ev->hist = g_hash_table_new(NULL, NULL);
	
	// empty history for root event
	hist_t *h0 = (hist_t *)MYcalloc(sizeof(hist_t));
	h0->e = ev;
	size_mark(h0);
	g_hash_table_insert(ev->hist, h0, h0);
	// initialize co-conditions:
	co_t *co = co_new(ev->postset->count);
	int i;
	for (i=0; i<ev->postset->count; i++) {
		co->conds[i].cond = (cond_t *)array_get(ev->postset, i);
		co->conds[i].hists = (hist_t **)MYmalloc(sizeof(hist_t *));
		co->conds[i].hists_len = 1;
		co->conds[i].hists[0] = h0;
		g_hash_table_insert(co->conds[i].cond->co_private, h0, co_new(0));
	}
	g_hash_table_insert(ev->co, h0, co);
	g_hash_table_insert(ev->qco, h0, co_new(0));
	
	// Unfolding:
	pe_init();
	pe(h0);
	hist_t *h = NULL;
	i = 0;
	while ((h = pe_pop()) != NULL) {
		if (!cutoff(h)) {
			add_history(h);
			pe(h);
			i++;
		} else
			nodelist_push(&cutoff_list, h);
	}
	parikh_finish();
}
