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
	for (co_cond = co->conds; co_cond<co->conds+size; ++co_cond)
	{
		co_cond->cond = NULL;
		co_cond->hists = NULL;
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

hist_t **hist_intersect(hist_t **a, int len_a, hist_t **b, int len_b, int *len_c)
{
	int size_c = len_a < len_b ? len_a : len_b;
	hist_t	**last_a = a + len_a,
		**last_b = b + len_b,
		**c = MYmalloc(sizeof(hist_t *) * size_c);
	
	// intersects the history arrays
	while (a < last_a || b < last_b) {
		if (*a == *b) {
			c[(*len_c)] = *a;
			a++; b++; (*len_c)++;
		} else if (*a < *b) a++;
		else b++;
	}
	// TODO: strip the length of the array to the used size
}

/**
 * intersects two array of concurrent conditions for two pairs <b,H>, <b',H'>
 */
co_t *co_intersect(co_t *a, co_t *b)
{
	co_cond_t *cond_a = a->conds, *lastcond_a = a->conds + a->len,
		*cond_b = b->conds, *lastcond_b = b->conds + b->len;
		co_t *c = co_new(a->len < b->len ? a->len : b->len);
		co_cond_t *cond_c = c->conds;
	
	while (cond_a < lastcond_a || cond_b < lastcond_b) {
		if (cond_a->cond == cond_b->cond) {
			// a == b is a condition present in both co-arrays
			cond_c->cond = cond_a->cond;
			int len_c;
			// so find the intersection of both histories
			cond_c->hists = hist_intersect(cond_a->hists,
					cond_a->hists_len, cond_b->hists,
					cond_b->hists_len, &len_c);
			cond_c->hists_len = len_c;
			cond_a++; cond_b++; cond_c++; c->len++;
		} else if (cond_a->cond < cond_b->cond) {
			cond_a++;
		} else {
			cond_b++;
		}
		// TODO: strip the length of the array to the used size
	}
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
