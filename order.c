#include <stdio.h>
#include <string.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"

/**
 * Creates a new parikh vector
 */
parikh_vec_t *parikh_new ()
{
	parikh_vec_t *vec = MYmalloc(sizeof(parikh_vec_t));
	if (net->numtr > 0xFFFE)
	{
		fprintf(stderr, "Parikh vector has too few entries.\n");
		exit(1);
	}
	vec->last = vec->parikh = MYmalloc(net->numtr * sizeof(parikh_t));
	vec->size = vec->count = 0;
	vec->min = vec->max = 0;
	return vec;
}

/**
 * Finalizes a parikh vector
 */
void parikh_finish (parikh_vec_t *vec)
{
	free(vec->parikh);
	free(vec);
}

/**
 * Set the Parikh vector to empty.
 */
void parikh_reset (parikh_vec_t *vec)
{
	vec->count = 0;
}

/**
 * Add an appearance of transition number tr_num.
 */
void parikh_add (parikh_vec_t *vec, unsigned short int tr_num)
{
	vec->count++;
	if (tr_num < vec->last->tr_num)
	{	/* smaller than last insertion - search downwards */
		if (tr_num < vec->max)
			vec->last = vec->parikh - 1;
		else	
		{
			while (tr_num < (--vec->last)->tr_num);
			if (tr_num == vec->last->tr_num) goto parikh_add;
			else vec->last++;
		}
	}
	else if (tr_num > vec->last->tr_num)
	{	/* larger than last insertion - search upwards */
		if (tr_num > vec->parikh[vec->size].tr_num)
			vec->last = vec->parikh + vec->size - 1;
		else	
		{
			while (tr_num > (++vec->last)->tr_num);
			if (tr_num == vec->last->tr_num) goto parikh_add;
		}
	}
	else
		goto parikh_add;

	/* insert one appearance of tr_num at vec->last */
	memmove(vec->last+1, vec->last, sizeof(parikh_t)
		* (vec->size - (vec->last - vec->parikh)));
	vec->last->tr_num = tr_num;
	vec->last->appearances = 1;
	vec->size++;
	return;

	parikh_add: vec->last->appearances++;
}

/**
 * Finish vector
 */
void parikh_save (parikh_vec_t *vec)
{
	parikh_t *vector = MYmalloc(++vec->size * sizeof(parikh_t));
	vec->parikh[vec->size].tr_num = 0; /* mark the last array element */
	memcpy(vector, vec->parikh, vec->size * sizeof(parikh_t));
	vec->parikh = vector;
}

/**
 * Compares two Parikh vectors pe1 and pe2.
 * Returns -1 if pe1 < pe2, and 1 if pe1 > pe2, 0 if pe1 == pe2.
 */ 
int parikh_compare (parikh_t *pv1, parikh_t *pv2)
{
	while (pv1->tr_num && pv2->tr_num && (pv1->tr_num == pv2->tr_num)
			&& (pv1->appearances == pv2->appearances))
		pv1++, pv2++;

	if (!pv1->tr_num && !pv2->tr_num) return 0;
	if (pv1->tr_num == pv2->tr_num)
		return pv2->appearances - pv1->appearances;
	else
		return pv1->tr_num - pv2->tr_num;
}

int size_mark_rec(hist_t *hist, parikh_vec_t *vec)
{
	if (!HAS_FLAG(hist->flags, BLACK) && hist->e->num != -1) {
		SET_FLAG(hist->flags, BLACK);
		parikh_add(vec, hist->e->origin->num);
		int size = 1;

		pred_t *pred = hist->pred, *last = hist->pred + hist->pred_n;
		while (pred < last) {
			size += size_mark_rec(pred->hist, vec);
			pred++;
		}
		return size;
	} else
		return 0;
}

void size_mark_clean(hist_t *hist)
{
	if (HAS_FLAG(hist->flags, BLACK)) {
		CLEAN_FLAG(hist->flags, BLACK);

		pred_t *pred = hist->pred, *last = hist->pred + hist->pred_n;
		while (pred < last) {
			size_mark_clean(pred->hist);
			pred++;
		}
	}
}

void size_mark(hist_t *hist)
{
	parikh_vec_t *vec = parikh_new();
	int size = size_mark_rec(hist, vec);
	size_mark_clean(hist);
	hist->size = size;
	hist->parikh = vec;
}

/**
 * Computes ordering information for the possible extension e=(tr,pe_conds)
 * and returns a queue entry with that information. The ordering information
 * consists of the size and Parikh vector of [e]; the Foata normal form is
 * computed only when necessary.
 *
pe_queue_t* create_queue_entry (trans_t *tr)
{
	pe_queue_t *qu_new;
	event_t *ev, **queue;
	cond_t  *co, **co_ptr;
	nodelist_t *list;
	int sz;

	ev_mark++;
	*(queue = events) = NULL;

	parikh_reset();
	parikh_add(tr->num);

	// add the input events of the pre-conditions into the queue 
	for (sz = tr->preset_size, co_ptr = pe_conds; sz--; )
	{
		(co = *co_ptr++)->mark = ev_mark;
		if ((ev = co->pre_ev) && ev->mark != ev_mark)
			(*++queue = ev)->mark = ev_mark;
	}

	while ((ev = *queue))
	{
		queue--;
		parikh_add(ev->origin->num);

		// add the immediate predecessor events of ev to the queue
		for (sz = ev->origin->preset_size, co_ptr = ev->preset; sz--; )
		{
			(co = *co_ptr++)->mark = ev_mark;
			if ((ev = co->pre_ev) && ev->mark != ev_mark)
				(*++queue = ev)->mark = ev_mark;
		}
	}

	// create the queue element
        qu_new = MYmalloc(sizeof(pe_queue_t));
        qu_new->trans = tr;

        // copy the pre-conditions
        qu_new->conds = MYmalloc(tr->preset_size * sizeof(cond_t*));
        memcpy(qu_new->conds,pe_conds,tr->preset_size*sizeof(cond_t*));

	// copy Parikh vector
	qu_new->p_vector = parikh_save();
	qu_new->lc_size = parikh_count;

	// now compute the marking
	ev_mark++;
	*(queue = events) = NULL;
	qu_new->marking = NULL;

	for (sz = tr->preset_size, co_ptr = pe_conds; sz--; )
		if ((ev = (*co_ptr++)->pre_ev) && ev->mark != ev_mark)
			(*++queue = ev)->mark = ev_mark;

	while ((ev = *queue))
	{
		queue--;

		// check off the postset conditions
		for (sz = ev->origin->postset_size, co_ptr = ev->postset; sz--;)
			if ((co = *co_ptr++)->mark != ev_mark-1)
				nodelist_insert(&(qu_new->marking),co->origin);

		// add the immediate predecessor events of ev to the queue
		for (sz = ev->origin->preset_size, co_ptr = ev->preset; sz--; )
			if ((ev = (*co_ptr++)->pre_ev) && ev->mark != ev_mark)
				(*++queue = ev)->mark = ev_mark;
	}

	// add the post-places of tr 
	for (list = tr->postset; list; list = list->next)
		nodelist_insert(&(qu_new->marking), list->node);

	// add the places of unconsumed minimal conditions
	for (list = unf->m0; list; list = list->next)
		if ((co = list->node)->mark != ev_mark-1)
			nodelist_insert(&(qu_new->marking), co->origin);

	return qu_new;
}
*/

/**
 * Determine the Foata level of a possible extension.
 *
int find_foata_level (pe_queue_t *pe)
{
	int level = 1;
	int sz = pe->trans->preset_size;
        cond_t **co_ptr = pe->conds;
	event_t *ev;

	while (sz--)
	{
		if ((ev = (*co_ptr++)->pre_ev) && ev->foata_level >= level)
			level = ev->foata_level + 1;
	}

	return level;
}*/

/**
 * Identify the "slices" of the Foata normal form in the local configuration
 * of the possible extension pe.
 *
nodelist_t** create_foata_lists (pe_queue_t *pe)
{
	int sz, tr_level = find_foata_level(pe);
	nodelist_t **fo = MYcalloc((tr_level + 2) * sizeof(nodelist_t*));
	event_t *ev, **queue;
	cond_t **co_ptr;

	ev_mark++;
	*(queue = events) = NULL;

	for (sz = pe->trans->preset_size, co_ptr = pe->conds; sz--; )
		if ((ev = (*co_ptr++)->pre_ev) && ev->mark != ev_mark)
			(*++queue = ev)->mark = ev_mark;

	nodelist_push(fo + tr_level,pe->trans);

	while ((ev = *queue))
	{
		--queue;
		nodelist_push(fo + ev->foata_level, ev->origin);

		for (sz = ev->origin->preset_size, co_ptr = ev->preset; sz--; )
			if ((ev = (*co_ptr++)->pre_ev) && ev->mark != ev_mark)
				(*++queue = ev)->mark = ev_mark;
	}

	return fo;
}
*/

/**
 * Compare the Foata normal form of two local configurations.
 *
int foata_compare (pe_queue_t *pe1, pe_queue_t *pe2)
{
	// create the Foata "slices" for both configurations
	nodelist_t **fo1 = create_foata_lists(pe1);
	nodelist_t **fo2 = create_foata_lists(pe2);
	nodelist_t **f1 = fo1+1, **f2 = fo2+1, *list;
	parikh_t *pv1;
	int res = 0, pc1;

	while (*f1 && *f2)	// compare Parikh vectors, level by level
	{
		parikh_reset();
		for (list = *f1; list; list = list->next)
			parikh_add(((trans_t*)(list->node))->num);
		pc1 = parikh_count; pv1 = parikh_save();

		parikh_reset();
		for (list = *f2; list; list = list->next)
			parikh_add(((trans_t*)(list->node))->num);
		parikh[++parikh_size].tr_num = 0;

		res = pc1 - parikh_count;
		if (!res) res = parikh_compare(pv1,parikh+1);
		free(pv1);
		if (res) break;

		f1++, f2++;
	}

	for (f1 = fo1+1; *f1; f1++) nodelist_delete(*f1);
	for (f2 = fo2+1; *f2; f2++) nodelist_delete(*f2);
	free(fo1);
	free(fo2);

	return res;	// should never return 0
}
*/

/**
 * Compares two possible extensions according to the <_E order from [ERV02].
 * Returns -1 if pe1 < pe2, and 1 if pe1 > pe2, 0 otherwise (can't happen?).
 */
int pe_compare (hist_t *pe1, hist_t *pe2)
{
	int res;

	// Try to decide by local configuration size first.
	if (pe1->size < pe2->size) return -1;
	if (pe1->size > pe2->size) return 1;

	// Then decide by comparing the Parikh vectors.
	if ((res = parikh_compare(pe1->parikh->parikh, pe2->parikh->parikh)))
		return res;

	return 0;
	// TODO:
	// Finally, decide by Foata normal form.
	//return foata_compare(pe1,pe2);
}
