#include "common.h"
#include "unfold.h"

/*****************************************************************************/

/* The worklist of possible extensions is organized as a priority heap
   using an array (of pointers). The array is extended in steps of size
   PE_ALLOC_STEP as needed.						*/

#define PE_ALLOC_STEP 1024
pe_queue_t **pe_queue;		/* the priority array */
int pe_qsize, pe_qalloc;	/* current/maximum capacity */

/* This structure (a list of node lists) is used during the search for
   possible extensions to enumerate all potential sets conditions for a
   given transition.							*/
typedef struct pe_comb_t
{
	nodelist_t *current;
	nodelist_t *start;
} pe_comb_t;

pe_comb_t *pe_combs;	/* used in pe() */
cond_t   **pe_conds;	/* array of conditions, given by pe() to pe_insert() */
uchar     *pe0_conflicts;	/* conflicts of the initial conditions */

/*****************************************************************************/
/* Simple functions: initialize queue, release a queue entry, and release    */
/* memory allocated during initialization.				     */

void pe_init (nodelist_t *m0)
{
	int i;

	pe_qsize = 0;
	pe_queue = MYmalloc((pe_qalloc = PE_ALLOC_STEP) * sizeof(pe_queue_t*));
	
	pe_conds = MYmalloc(net->maxpre * sizeof(place_t*));
	pe_combs = MYmalloc(net->maxpre * sizeof(pe_comb_t));

	/* determine size of initial marking */
	for (i = 0; m0; m0 = m0->next) i++;
	pe0_conflicts = MYcalloc((i + 8) / 8);
}

void pe_free (pe_queue_t *qu)
{
	free(qu->conds);
	free(qu);
}

void pe_finish ()
{
	free(pe_conds);
	free(pe0_conflicts);
	free(pe_combs);
}

/*****************************************************************************/
/* Adds the possible extension (tr,pe_conds) to the priority queue.	     */

void pe_insert (trans_t *tr)
{
	pe_queue_t *qu_new = create_queue_entry(tr);
	int index = ++pe_qsize;

	if (pe_qsize >= pe_qalloc)
	{
		pe_qalloc += PE_ALLOC_STEP;
		pe_queue = MYrealloc(pe_queue,pe_qalloc * sizeof(pe_queue_t*));
	}

	/* insert new element at the end, then move upwards as needed */
	for (; index > 1; index /= 2)
	{
		if (pe_compare(qu_new,pe_queue[index/2]) > 0) break;
		pe_queue[index] = pe_queue[index/2]; /* move parent downwards */
	}
	pe_queue[index] = qu_new;
}

/*****************************************************************************/
/* Remove the minimal event from the queue and restore order.		     */

pe_queue_t* pe_pop ()
{
	pe_queue_t *first = pe_queue[1];
	pe_queue_t *last;
	int index = 1, newindex;

	if (!pe_qsize) return NULL;

	last = pe_queue[pe_qsize--];
	for (;;)	/* sift last element downwards */
	{
		if (index > pe_qsize / 2) break;
		/* compare "last" and children of index */
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
		pe_queue[index] = pe_queue[newindex];	/* move child upwards */
		index = newindex;
	}
	pe_queue[index] = last;
	return first;
}

/*****************************************************************************/
/* Check whether any pair of conditions downwards from curr is in conflict   */
/* The check excludes the condition given to pe(), because we already know   */
/* that that one is not in conflict with any of the others.		     */

char pe_conflict (pe_comb_t *curr)
{
	int sz;
	cond_t *co, **co_ptr;
	event_t *ev, **queue;

	/* just one condition - no conflict */
	if (curr == pe_combs) return 0;

	++ev_mark;
	*(queue = events) = NULL;

	/* put the pre-events into the queue */
	while (curr >= pe_combs)
	{
		(co = (curr--)->current->node)->mark = ev_mark;
		if ((ev = co->pre_ev) && ev->mark != ev_mark)
			 (*++queue = ev)->mark = ev_mark;
	}

	/* go upwards, try to find two paths converging at some condition */
	while ((ev = *queue))
	{
		queue--;
		for (sz = ev->origin->preset_size, co_ptr = ev->preset; sz--; )
		{
			if ((co = *co_ptr++)->mark == ev_mark) return 1;
			co->mark = ev_mark;
			if ((ev = co->pre_ev) && ev->mark != ev_mark)
				 (*++queue = ev)->mark = ev_mark;
		}
	}

	return 0;
}

/*****************************************************************************/
/* Find the new possible extensions created by the addition of co.	     */

void pe (cond_t *co)
{
	nodelist_t *pl_post, *tr_pre, **compat_conds;
	pe_comb_t *curr_comb;
	cond_t **cocoptr;
	place_t *pl = co->origin, *pl2;
	trans_t *tr;

	*pe_conds = co;	/* any new PE contains co */
	nodelist_push(&(pl->conds),co);

	/* check the transitions in pl's postset */
	for (pl_post = pl->postset; pl_post; pl_post = pl_post->next)
	{
		tr = pl_post->node;
		(curr_comb = pe_combs)->start = NULL;

		/* for every other post-place of tr, collect the conditions
			that are co-related to co in the comb structure */
		for (tr_pre = tr->preset; tr_pre; tr_pre = tr_pre->next)
		{
			if ((pl2 = tr_pre->node) == pl) continue;

			compat_conds = &(curr_comb->start);
			cocoptr = ((cond_t**)(co->coarray_common))+1;
			while (*++cocoptr)
				if ((*cocoptr)->origin == pl2)
				    nodelist_push(compat_conds,*cocoptr);
			cocoptr = ((cond_t**)(co->coarray_private))+1;
			while (*++cocoptr)
				if ((*cocoptr)->origin == pl2)
				    nodelist_push(compat_conds,*cocoptr);

			if (!*compat_conds) break;

			curr_comb->current = curr_comb->start;
			(++curr_comb)->start = NULL;
		}

		/* find all non-conflicting combinations in the comb */
		curr_comb = pe_combs;
		if (!tr_pre) while (curr_comb >= pe_combs)
		{
			if (!curr_comb->start)
			{
				cond_t **co_ptr = pe_conds;
				for (curr_comb = pe_combs; curr_comb->start;
						curr_comb++)
					*++co_ptr = curr_comb->current->node;
				pe_insert(tr);
				curr_comb--;
			}
			else if (!pe_conflict(curr_comb))
			{
				curr_comb++;
				continue;
			}

			while (curr_comb >= pe_combs && !(curr_comb->current =
						curr_comb->current->next))
			{
				curr_comb->current = curr_comb->start;
				curr_comb--;
			}
		}

		/* release the comb lists */
		for (curr_comb = pe_combs; curr_comb->start; curr_comb++)
			nodelist_delete(curr_comb->start);
	}
}
