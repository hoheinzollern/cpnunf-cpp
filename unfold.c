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

/*****************************************************************************/
/* The co-relation is kept in the form of an incidence list. Every condition */
/* keeps two lists of conditions which are concurrent to it. The first list, */
/* stored in the coarray_common field, stores the conditions that are con-   */
/* current to all conditions with the same event as their singleton preset.  */
/* The second list, coarray_private, contains additional conditions which do */
/* not (necessarily) enjoy this property.				     */

/* The structure of a coarray is as follows: The first field contains the    */
/* number of allocated elements (minus header and tail). The second field    */
/* contains the number of elements currently in use. After that, pointers    */
/* to the concurrent transitions follow, the end is signalled by a NULL.     */

/* Create an empty coarray with 'size' allocated events. */
COARRAY_TYPE* alloc_coarray (int size)
{
	COARRAY_TYPE *newarray = MYmalloc((size+3) * sizeof(COARRAY_TYPE));
	newarray[0] = size;
	newarray[1] = 0;
	newarray[2] = 0;
	return newarray;
}

/* Add a single condition to an array, enlarging the array if necessary. */
void addto_coarray (COARRAY_TYPE **array, cond_t *co)
{
	int pos;

	if ((*array)[1] == (*array)[0])
	{
		COARRAY_TYPE newsize = ((*array)[0] + 1) + ((*array)[0] / 4);
		*array = MYrealloc(*array,(newsize+3) * sizeof(COARRAY_TYPE));
		(*array)[0] = newsize;
	}
	pos = 2 + (*array)[1]++;
	(*array)[pos] = (COARRAY_TYPE)co;
	(*array)[pos+1] = 0;
}

/* Copy an array, truncating it to the necessary size. */
COARRAY_TYPE* coarray_copy (COARRAY_TYPE* array)
{
	COARRAY_TYPE *newarray = MYmalloc((array[1]+3) * sizeof(COARRAY_TYPE));
	newarray[0] = array[1];
	memcpy(newarray+1,array+1,(array[1]+2) * sizeof(COARRAY_TYPE));
	return newarray;
}

/**
 * Insert a condition into the unfolding. The new condition is labelled with
 * the place pl. If ev is present then it is added to phantom, the collection
 * of read arcs.
 */
cond_t* insert_condition (place_t *pl, event_t *ev)
{
	nodelist_t *list;

        cond_t *co = MYmalloc(sizeof(cond_t));
        co->next = unf->conditions;
        unf->conditions = co;

	/**
	 * remember relation between co and pl
	 * the other direction is done in pe()
	 */
	co->origin = pl;

        co->postset = NULL;
	co->pre_ev = ev;
	co->mark = 0;
	co->num = unf->numco++;

	co->phantom = co;	/* default setting, may be changed below */

	if (!ev) return co;

	/**
	 * Is this place connected with a read arc? If yes, find the
	 * corresponding place in the preset of the event and set
	 * co->phantom accordingly.
	 */
	for (list = ev->origin->readarcs; list; list = list->next)
		if (list->node == pl)
		{
			int i;
			for (i = 0; i < ev->preset_size; i++)
				if (ev->preset[i]->origin == pl)
					co->phantom = ev->preset[i]->phantom;
		}

	return co;
}

/**
 * Insert an event into the unfolding. The new event is derived from
 * qu->trans and the conditions in qu->conds form its preset.
 */
event_t* insert_event (pe_queue_t *qu)
{
        event_t *ev = MYmalloc(sizeof(event_t));
	int sz = qu->trans->preset_size;
	cond_t **co_ptr;

        ev->next = unf->events;
        unf->events = ev;
	ev->origin = qu->trans;
	ev->mark = 0;		/* for marking_of */
	ev->coarray = NULL;
	ev->foata_level = find_foata_level(qu);
	ev->preset_size = qu->trans->preset_size;
	ev->postset_size = qu->trans->postset_size;

	/* add preset (postset comes later) */
        ev->preset = co_ptr = MYmalloc(sz * sizeof(cond_t*));
	memcpy(ev->preset,qu->conds,sz * sizeof(cond_t*));
	while (sz--) nodelist_push(&((*co_ptr++)->postset),ev);

	/* allocate memory for queue in conco_nt if necessary */
	if (++unf->numev >= events_size)
	{
		events_size += ce_alloc_step;
		events = MYrealloc(events,events_size * sizeof(event_t*));
	}

	return ev;
}

enum { CUTOFF_NO, CUTOFF_YES };

/**
 * Add the post-conditions of event ev and compute the possible extensions.
 */
void add_post_conditions (event_t *ev, char cutoff)
{
	cond_t **co_ptr, **cocoptr;
	nodelist_t *list;
	COARRAY_TYPE *newarray;

	/**
	 * First insert the conditions without putting them in pl->conds;
	 * that is done by pe() to avoid duplicated new events.
	 */
	ev->postset = co_ptr
		= MYmalloc(ev->postset_size * sizeof(cond_t*));
	for (list = ev->origin->postset; list; list = list->next)
		*co_ptr++ = insert_condition(list->node,ev);

	if (cutoff) return;

	/**
	 * Having computed the common part of the co-relation for all
	 * conditions in co_relation(), we create a copy that uses only
	 * the necessary amount of memory.
	 */
	newarray = coarray_copy(ev->coarray);
	free(ev->coarray);

	/* Add the reverse half of the concurrency relation. */
	cocoptr = ((cond_t**)(newarray))+1;
	while (*++cocoptr)
	{
		co_ptr = ev->postset;
		for (list = ev->origin->postset; list; list = list->next)
			addto_coarray(&((*cocoptr)->coarray_private),*co_ptr++);
	}

	co_ptr = ev->postset;
	for (list = ev->origin->postset; list; list = list->next)
	{
		/* record co-relation between new conditions */
		(*co_ptr)->coarray_common = newarray;
		(*co_ptr)->coarray_private = alloc_coarray(0);
		cocoptr = ev->postset;
		while (cocoptr != co_ptr)
		{
			addto_coarray(&((*co_ptr)->coarray_private),*cocoptr);
			addto_coarray(&((*cocoptr)->coarray_private),*co_ptr);
			cocoptr++;
		}

		/* compute possible extensions for each new condition */
		pe(*co_ptr++);
	}
}

typedef struct cqentry_t {
	cond_t *co;
	int index;
	struct cqentry_t *next;
} cqentry_t;

/**
 * This maintains a queue of conditions used for computing the intersection.
 */
void insert_to_queue (cqentry_t **queue, cqentry_t *newentry,
			cond_t *co, int index)
{
	newentry->co = co;
	newentry->index = index;

	while (*queue && (*queue)->co->num < co->num)
		queue = &((*queue)->next);
	newentry->next = *queue;
	*queue = newentry;
}

/**
 * Function co_relation computes the set of conditions that are concurrent
 * to the newly added event ev. That set of conditions is also concurrent to
 * the postset of ev and forms the common part of their concurrency list.
 * The set is essentially computed by taking the intersection of the sets of
 * conditions concurrent to the input conditions of ev.
 */
void co_relation (event_t *ev)
{
	cond_t  **co_ptr, ***colists;
	int	  evps = ev->preset_size, sz;
	cqentry_t *queue = NULL;
	char	finished = 0, *switched;

	/* Find the maximal potential size of the intersection. */
	int min = 0xfffffff;
	for (sz = evps, co_ptr = ev->preset; sz--; co_ptr++)
	{
		int cosize = (*co_ptr)->coarray_common[1] +
				(*co_ptr)->coarray_private[1];
		if (min > cosize) min = cosize;
	}
	ev->coarray = alloc_coarray(min + ev->postset_size);

	/* Add first condition in each list to a "priority queue"
	   ordered by condition numbers. */
	colists = MYmalloc(evps * sizeof(cond_t**));
	switched = MYmalloc(evps * sizeof(char));
	for (sz = evps, co_ptr = ev->preset+(evps-1); sz--; co_ptr--)
	{
		colists[sz] = ((cond_t**)((*co_ptr)->coarray_common))+2;
		switched[sz] = 0;
		if (!*colists[sz])
		{
			switched[sz] = 1;
			colists[sz]=((cond_t**)((*co_ptr)->coarray_private))+2;
			if (!*colists[sz]) { finished = 1; break; }
		}
		if (*colists[sz])
			insert_to_queue(&queue, MYmalloc(sizeof(cqentry_t)),
					*(colists[sz]++),sz);
	}

	/* Take the next lowest condition out of the queue, check whether
	   it occurred in all input conditions, and feed the successors
	   into the queue. */
	while (!finished)
	{
		cond_t *minco = queue->co;
		int min = minco->num, count = 0;

		while (queue && queue->co->num == min)
		{
			cqentry_t *tmp = queue;
			int index = tmp->index;
			queue = queue->next;
			count++;

			if (!*colists[index])
			{
				if (!switched[index]++)
					colists[index] = ((cond_t**)
					(ev->preset[index]->coarray_private))+2;

				if (!*colists[index])
				{
					free(tmp); finished = 1;
					continue;
				}
			}
			insert_to_queue(&queue,tmp,*(colists[index]++),index);
		}

		if (count == evps) addto_coarray(&(ev->coarray),minco);
	}

	free(colists);
	free(switched);
	while (queue)
	{
		cqentry_t *tmp = queue;
		queue = queue->next;
		free(tmp);
	}
}

void recursive_add (nodelist_t *pre, nodelist_t *current)
{
	if (!pre) return;
	recursive_add(pre->next,current);
	addto_coarray(&(((cond_t*)(pre->node))->coarray_private),current->node);
	addto_coarray(&(((cond_t*)(current->node))->coarray_private),pre->node);
}

void recursive_pe (nodelist_t *list)
{
	if (!list) return;
	recursive_pe(list->next);
	recursive_add(list->next,list);
	pe(list->node);
}

/*****************************************************************************/

/**
 * Computes the unfolding of the net
 */
void unfold ()
{
	nodelist_t *list;
	pe_queue_t *qu;
	place_t *pl;
	event_t *ev;
	cond_t  *co;
	int cutoff;

	/* create empty unfolding structure */
	unf = nc_create_unfolding();

	/* initializations for backward search algorithms */
	ev_mark = 0;
	events_size = conditions_size = ce_alloc_step = (net->maxpre > 2000)?
			(net->maxpre + net->maxra + 8) & 0xFFFFFFF8 : 2000;
	events = MYmalloc(events_size * sizeof(event_t*));

	/* cut-off events, corresponding events */
	cutoff_list = corr_list = NULL;

	/* init hash table, add initial marking */
	marking_init(); unf->m0 = NULL;
	add_marking(list = marking_initial(),NULL);

	/* initialize PE computation */
	pe_init(list);
	parikh_init();

	/* add initial conditions to unfolding, compute possible extensions */
	for (; list; list = list->next)
	{
		co = insert_condition(pl = list->node,NULL);
		co->coarray_common = alloc_coarray(0);
		co->coarray_private = alloc_coarray(0);
		nodelist_push(&(unf->m0),co);
	}
	recursive_pe(unf->m0);

	/* take the next event from the queue */
	while ((qu = pe_pop()))
	{
		/* add event to the unfolding */
		ev = insert_event(qu);
		cutoff = add_marking(qu->marking,ev);
		pe_free(qu);

		/* if we've found the -T transition, stop immediately */
		if (stoptr && ev->origin == stoptr) { exitcode = 2; goto clean;}

		/* if the marking was already represented in the unfolding,
		   we have a cut-off event */
		if (!cutoff) { unf->events = unf->events->next; continue; }

		/* compute the co-relation for ev and post-conditions */
		co_relation(ev);

		/* add post-conditions, compute possible extensions */
		add_post_conditions(ev,CUTOFF_NO);
	}

	/* add post-conditions for cut-off events */
	for (list = cutoff_list; list; list = list->next)
	{
		ev = list->node;
		ev->next = unf->events; unf->events = ev;
		add_post_conditions(ev,CUTOFF_YES);
	}

	/* release memory that is no longer needed (possibly incomplete) */
clean:	pe_finish();
	parikh_finish();
	free(events);

	for (pl = net->places; pl; pl = pl->next)
		nodelist_delete(pl->conds);
}
