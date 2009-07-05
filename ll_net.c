#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"
#include "output.h"

void print_ll_event(event_t *ev)
{
	if (ev->num != -1)
		printf("%d\"e%d (%s)\"\n", ev->num,ev->num,ev->origin->name);
}

void print_ll_pre(cond_t *co)
{
	if (co->pre_ev->num != -1)
		printf("%d<%d\n", co->pre_ev->num, co->num);
}

void print_ll_readarcs(cond_t *co)
{
	array_t *array = co->readarcs;
	event_t *ev = NULL;
	int i;
	for (i=0; i<array->count; i++) {
		ev = (event_t *)array_get(array, i);
		printf("%d<%d\n", ev->num, co->num);
	}
}

void print_ll_postset(cond_t *co)
{
	array_t *array = co->postset;
	event_t *ev = NULL;
	int i;
	for (i=0; i<array->count; i++) {
		ev = (event_t *)array_get(array, i);
		printf("%d>%d\n", ev->num, co->num);
	}
}

void print_ll_condition(cond_t *co)
{
	printf("%d\"b%d (%s)\"\n", co->num, co->num, co->origin->name);
}

void print_ll_history_rec(FILE *stream, hist_t *h)
{
	if (!HAS_FLAG(h->flags, BLACK) && h->e->num!=-1) {
		SET_FLAG(h->flags, BLACK);

		fprintf(stream, "%d ", h->e->num);
		pred_t *pred = h->pred, *last = h->pred + h->pred_n;
		while (pred < last) {
			print_ll_history_rec(stream, pred->hist);
			++pred;
		}
	}
}

void history_cleanup(hist_t *h)
{
	if (HAS_FLAG(h->flags, BLACK)) {
		CLEAN_FLAG(h->flags, BLACK);

		pred_t *pred = h->pred, *last = h->pred + h->pred_n;
		while (pred < last) {
			history_cleanup(pred->hist);
			++pred;
		}
	}
}

void print_ll_history(FILE *stream, hist_t *h)
{
	fprintf(stream, "H[%d]={ ", h->e->num);
	print_ll_history_rec(stream, h);
	fprintf(stream, "}\n");
	history_cleanup(h);
}

void write_ll_net (unf_t *u, nodelist_t *cutoffs, UNFbool hist)
{
	nodelist_t *list;

	GHashTableIter iter;
	gpointer key, value;

	// Header:
	printf("PEP\nPetriBox\nFORMAT_N2\n");

	// Conditions:
	printf("PL\n");
	g_hash_table_iter_init (&iter, unf->conditions);
	while (g_hash_table_iter_next (&iter, &key, &value))
		print_ll_condition((cond_t *)value);

	// Events:
	printf("TR\n");
	g_hash_table_iter_init (&iter, unf->events);
	while (g_hash_table_iter_next (&iter, &key, &value))
		print_ll_event((event_t *)value);

	// Transition -> Place
	printf("TP\n");
	g_hash_table_iter_init (&iter, unf->conditions);
	while (g_hash_table_iter_next (&iter, &key, &value))
		print_ll_pre((cond_t *)value);

	// Place -> Transition
	printf("PT\n");
	g_hash_table_iter_init (&iter, unf->conditions);
	while (g_hash_table_iter_next (&iter, &key, &value))
		print_ll_postset((cond_t *)value);

	// Readarcs
	printf("RA\n");
	g_hash_table_iter_init (&iter, unf->conditions);
	while (g_hash_table_iter_next (&iter, &key, &value))
		print_ll_readarcs((cond_t *)value);

	if (hist) {
		// Histories
		printf("H\n");
		g_hash_table_iter_init (&iter, unf->events);
		while (g_hash_table_iter_next (&iter, &key, &value)) {
			event_t *ev = (event_t *)value;
			GHashTableIter hiter;
			g_hash_table_iter_init(&hiter, ev->hist);
			while (g_hash_table_iter_next (&hiter, &key, &value)) {
				print_ll_history(stdout, (hist_t*)value);
			}
		}
	}

	int num_cutoffs = 0;
	for (list = cutoffs; list; list = list->next)
	{
		num_cutoffs++;
		hist_t *h = ((hist_t *)list->node);
		fprintf(stderr, "cutoff history for (%s);\n",
			((trans_t*)h->e)->name);
	}

	fprintf(stderr, "%d cutoff histories\n", num_cutoffs);
}
