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
 *
void pe_insert (hist_t *h)
{
	hist_t *qu_new = create_queue_entry(tr);
	int index = ++pe_qsize;

	if (pe_qsize >= pe_qalloc)
	{
		pe_qalloc += PE_ALLOC_STEP;
		pe_queue = MYrealloc(pe_queue,pe_qalloc * sizeof(pe_queue_t*));
	}

	// insert new element at the end, then move upwards as needed
	for (; index > 1; index /= 2)
	{
		if (pe_compare(qu_new,pe_queue[index/2]) > 0) break;
		pe_queue[index] = pe_queue[index/2]; // move parent downwards
	}
	pe_queue[index] = qu_new;
}*/

/**
 * Remove the minimal event from the queue and restore order.
 *
pe_queue_t* pe_pop ()
{
	pe_queue_t *first = pe_queue[1];
	pe_queue_t *last;
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
}*/

/**
 * @arg e an event
 * @return im(e* U _e_) subset of S
 */
array_t *im_post_context(event_t *e)
{
	int len = e->postset->len + e->readarcs->len;
	array_t *places = array_new(len);
	int i = 0;
	for (i = 0; i < e->postset->len; i++)
		array_append(places, ((cond_t *)
			array_get(e->postset, i))->origin);
	for (i = 0; i < e->readarcs->len; i++)
		array_append(places, ((cond_t *)
			array_get(e->readarcs, i))->origin);
	return places;
}

/**
 * Computes the postset of a set of places S
 * @arg S the unordered set of places
 * @arg T the ordered set of transitions
 */
array_t *place_postset(array_t *S)
{
	array_t *T = array_new(1);
	int i;
	for (i = 0; i < S->len; i++) {
		nodelist_t *post = ((place_t *)array_get(S, i))->postset;
		while (post != NULL) {
			array_insert(T, post->node);
			post = post->next;
		}
		nodelist_t *cont = ((place_t *)array_get(S, i))->readarcs;
		while (cont != NULL) {
			array_insert(T, cont->node);
			cont = cont->next;
		}
	}
}

inline place_t *place(co_cond_t *co_cond)
{
	return co_cond->cond->origin;
}

/**
 * Test whether *tr U _tr_ in co and returns the set of conditions that need to
 * be pairwise concurrent to create a new history for an event e;
 */
co_t *test_trans(trans_t *tr, co_t *co)
{
	nodelist_t *pre = tr->preset;
	nodelist_t *context = tr->readarcs;
	UNFbool good = UNF_TRUE;
	while (pre != NULL && good == UNF_TRUE) {
		// TODO: optimize this part: sets of places in the original net
		// should be kept ordered.
		
		pre = pre->next;
	}
}

/**
 * Find the new possible extensions created by the addition of h.
 */
void pe (hist_t *h)
{
	array_t *S = im_post_context(event_t *e)
	// T gets the list of transitions enabled by places in the postset
	// and context of e.
	array_t *T = place_postset(S);
	array_delete(S);
	
	co_t *co = (co_t *)g_hash_table_lookup(h->e->co, h);
	
}
