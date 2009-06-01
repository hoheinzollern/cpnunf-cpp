#include "common.h"
#include "unfold.h"

/*****************************************************************************/

/**
 * The worklist of possible extensions is organized as a priority heap
 * using an array (of pointers). The array is extended in steps of size
 * PE_ALLOC_STEP as needed.
 */

#define PE_ALLOC_STEP 1024
hist_t **pe_queue;		/* the priority array */
int pe_qsize, pe_qalloc;	/* current/maximum capacity */

/**
 * Adds the possible extension (tr,pe_conds) to the priority queue.
 */
void pe_insert (hist_t *h)
{
	hist_t *qu_new = create_queue_entry(tr);
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

/**
 * Remove the minimal event from the queue and restore order.
 */
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

/**
 * Find the new possible extensions created by the addition of co.
 */
void pe (event_t *ev)
{
}
