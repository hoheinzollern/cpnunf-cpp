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
 * Function co_relation computes the set of conditions that are concurrent
 * to the newly added event ev. That set of conditions is also concurrent to
 * the postset of ev and forms the common part of their concurrency list.
 * The set is essentially computed by taking the intersection of the sets of
 * conditions concurrent to the input conditions of ev.
 */
void co_relation (event_t *ev)
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
