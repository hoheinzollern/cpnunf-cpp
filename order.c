#include <stdio.h>
#include <string.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"

parikh_t *parikh;
parikh_t *pa_last;

int parikh_count;	/* counts the total number of elements in the vector */
int parikh_size;	/* counts the number of different transitions        */

/**
 * Creates a new parikh vector
 */
void parikh_init ()
{
	if (net->numtr > 0xFFFE)
	{
		fprintf(stderr,"Parikh vector has too few entries.\n");
		exit(1);
	}
	parikh = MYmalloc((net->numtr + 2) * sizeof(parikh_t));
}

/**
 * Finalizes a parikh vector
 */
void parikh_finish ()
{
	free(parikh);
}

/**
 * Set the Parikh vector to empty.
 */
void parikh_reset ()
{
	/* The entries 0 and 1 serve as boundary elements. */
	parikh[0].tr_num = 0;
	parikh[1].tr_num = 0;

	parikh_count = 0;
	parikh_size = 0;

	/* Assuming that causally related events are due to transitions
	   whose numbers are near to each other, we start searching for
	   additional transitions near the last insertion.		*/
	pa_last = parikh + 1;
}

/**
 * Add an appearance of transition number tr_num.
 */
void parikh_add (int tr_num)
{
	parikh_count++;
	if (tr_num < pa_last->tr_num)
	{	/* smaller than last insertion - search downwards */
		if (tr_num < parikh[1].tr_num)
			pa_last = parikh + 1;
		else
		{
			while (tr_num < (--pa_last)->tr_num);
			if (tr_num == pa_last->tr_num) goto parikh_add;
			else pa_last++;
		}
	}
	else if (tr_num > pa_last->tr_num)
	{	/* larger than last insertion - search upwards */
		if (tr_num > parikh[parikh_size].tr_num)
			pa_last = parikh + parikh_size + 1;
		else
		{
			while (tr_num > (++pa_last)->tr_num);
			if (tr_num == pa_last->tr_num) goto parikh_add;
		}
	}
	else
		goto parikh_add;

	/* insert one appearance of tr_num at pa_last */
	memmove(pa_last+1, pa_last, sizeof(parikh_t)
		* (2 + parikh_size - (pa_last - parikh)));
	pa_last->tr_num = tr_num;
	pa_last->appearances = 1;
	parikh_size++;
	return;

	parikh_add: pa_last->appearances++;
}

/**
 * Finish vector
 */
parikh_t* parikh_save ()
{
	parikh_t *vector = MYmalloc(++parikh_size * sizeof(parikh_t));
	parikh[parikh_size].tr_num = 0; /* mark the last array element */
	memcpy(vector, parikh+1, parikh_size * sizeof(parikh_t));
	return vector;
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

int size_mark_rec(hist_t *hist, guchar *marking)
{
	if (hist->e->num == -1) {
		nodelist_t *n = unf->m0;
		for (; n != NULL; n = n->next)
			marking[((place_t*)n->node)->num-1] = 1;
		return 0;
	} else if (!HAS_FLAG(hist->flags, BLACK)) {
		SET_FLAG(hist->flags, BLACK);
		parikh_add(hist->e->origin->num);
#ifdef __DEBUG__
		fprintf(stderr, "%s ", hist->e->origin->name);
#endif

		int size = 1;
		pred_t *pred = hist->pred, *last = hist->pred + hist->pred_n;
		while (pred < last) {
			size += size_mark_rec(pred->hist, marking);
			pred++;
		}

		nodelist_t *n = hist->e->origin->preset;
		for (; n != NULL; n = n->next)
			marking[((place_t*)n->node)->num-1] = 0;
		n = hist->e->origin->postset;
		for (; n != NULL; n = n->next)
			marking[((place_t*)n->node)->num-1] = 1;

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
#ifdef __DEBUG__
	fprintf(stderr, "H:");
#endif
	parikh_reset();
	hist->marking = (guchar *)MYcalloc(sizeof(guchar) * net->numpl);
	hist->size = size_mark_rec(hist, hist->marking);
	hist->parikh = parikh_save();
	size_mark_clean(hist);
#ifdef __DEBUG__
	fprintf(stderr, "\n");
#endif
}

/**
 * Compares two possible extensions according to the <_E order from [ERV02].
 * Returns -1 if pe1 < pe2, and 1 if pe1 > pe2, 0 otherwise (can't happen?).
 */
int pe_compare (hist_t *pe1, hist_t *pe2)
{
//	int res;

	// Try to decide by local configuration size first.
	if (pe1->size < pe2->size) return -1;
	if (pe1->size > pe2->size) return 1;

	// Then decide by comparing the Parikh vectors.
//	if ((res = parikh_compare(pe1->parikh, pe2->parikh)))
//		return res;

	return 0;
	// TODO:
	// Finally, decide by Foata normal form.
	//return foata_compare(pe1,pe2);
}
