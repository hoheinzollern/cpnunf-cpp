#include <string.h>

#include "common.h"
#include "netconv.h"
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

enum { CUTOFF_NO, CUTOFF_YES };

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
	co_cont_t *co_cond, orig_cond = orig->conds;
	for (co_cond = co->conds; co_cond<co->conds+size;
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
	int size_b = len_b;
	*len_b = 0;
	hist_t	**last_a = a + len_a,
		**last_b = *b + len_b,
		**cur_b = *b;
	
	// intersects the history arrays
	while (a < last_a || *b < last_b) {
		if (*a == **b) {
			*cur_b = a;
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
	
	while (cond_a < lastcond_a || cond_b < lastcond_b) {
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
 * Computes the intersection between the co union qco and int;
 * stores the result in int.
 */
void co_u_qco_intersect(co_t *co, co_t *qco, co_t *int)
{
}

/**
 * takes a co structure and eliminates the preset of a given event
 * note that preset and the co structure are both ordered on conditions
 */
void co_drop_preset(co_t *co, event_t *ev)
{
	co_cond_t *cond1 = co->conds, *cond2 = co->conds,
		*lastcond = co->conds + co->len;
	GArray *pre = ev->preset;
	int i = 0;
	
	while (i < pre->len || cond2 < lastcond) {
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
 * computes the union of two co relations
 */
co_t *co_union(co_t *a, co_t *b)
{
	
}

co_t *co_relation(hist_t *hist)
{
	
}

co_t *qco_relation(hist_t *hist)
{
}

void add_history(hist_t *hist)
{
	event_t *e = hist->e;
	// Finds if an event is in the unfolding:
	if (!g_hash_table_lookup(unf->events, hist->e))
	{
		nc_add_event(e);
	}
	g_hash_table_insert(e->hist, hist, hist);
}

/*****************************************************************************/

/**
 * Computes the unfolding of the net
 */
void unfold ()
{
}
