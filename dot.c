#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"
#include "output.h"
#include "test.h"

void print_dot_event(event_t *ev)
{
	if (ev->num != -1)
		printf("  e%d [label=\"e%d (%s)\" shape=box];\n",
			ev->num,ev->num,ev->origin->name);
}

void print_dot_readarcs(cond_t *co)
{
	array_t *array = co->readarcs;
	event_t *ev = NULL;
	int i;
	for (i=0; i<array->count; i++) {
		ev = (event_t *)array_get(array, i);
		printf("  b%d -> e%d [dir=none];\n", co->num, ev->num);
	}
}

void print_dot_postset(cond_t *co)
{
	array_t *array = co->postset;
	event_t *ev = NULL;
	int i;
	for (i=0; i<array->count; i++) {
		ev = (event_t *)array_get(array, i);
		printf("  b%d -> e%d;\n", co->num, ev->num);
	}
}

void print_dot_condition(cond_t *co)
{
	printf("  b%d [label=\"b%d (%s)\" shape=circle];\n",
			co->num,co->num,co->origin->name);
	if (co->pre_ev->num != -1)
		printf("  e%d -> b%d;\n", co->pre_ev->num, co->num);
	print_dot_postset(co);
	print_dot_readarcs(co);
}

void print_dot_history_rec(FILE *stream, hist_t *h)
{
	if (!HAS_FLAG(h->flags, BLACK) && h->e->num!=-1) {
		SET_FLAG(h->flags, BLACK);

		fprintf(stream, "%d (%s) ", h->e->num, h->e->origin->name);
		pred_t *pred = h->pred, *last = h->pred + h->pred_n;
		while (pred < last) {
			print_dot_history_rec(stream, pred->hist);
			++pred;
		}
	}
}

void dot_history_cleanup(hist_t *h)
{
	if (HAS_FLAG(h->flags, BLACK)) {
		CLEAN_FLAG(h->flags, BLACK);

		pred_t *pred = h->pred, *last = h->pred + h->pred_n;
		while (pred < last) {
			dot_history_cleanup(pred->hist);
			++pred;
		}
	}
}

void print_dot_cutoff(hist_t *h)
{
	UNFbool created;
	event_t *ev = get_or_create_event(h, &created);
	if (created) {
		printf("  e%d [label=\"e%d (%s)\" shape=box style=dashed];\n",
			ev->num, ev->num, ev->origin->name);
		int i = 0;
		for (i = 0; i < ev->preset->count; i++) {
			cond_t *co = (cond_t*)array_get(ev->preset, i);
			printf("  b%d -> e%d;\n", co->num, ev->num);
		}
		for (i = 0; i < ev->readarcs->count; i++) {
			cond_t *co = (cond_t*)array_get(ev->readarcs, i);
			printf("  b%d -> e%d [dir=none];\n", co->num, ev->num);
		}
	}
	h->e = ev;
	fprintf(stderr, "H[%d] = { ", ev->num);
	print_dot_history_rec(stderr, h);
	dot_history_cleanup(h);
	fprintf(stderr, "}\n");
}

void write_dot_output (unf_t *u, nodelist_t *cutoffs)
{
	nodelist_t *list;

	GHashTableIter iter;
	gpointer key, value;

	printf("digraph test {\n");

	g_hash_table_iter_init (&iter, unf->events);
	while (g_hash_table_iter_next (&iter, &key, &value))
		print_dot_event((event_t *)value);

	g_hash_table_iter_init (&iter, unf->conditions);
	while (g_hash_table_iter_next (&iter, &key, &value)) 
		print_dot_condition((cond_t *)value);

	int num_cutoffs = 0;
	for (list = cutoffs; list; list = list->next)
	{
		num_cutoffs++;
		hist_t *h = ((hist_t *)list->node);
		fprintf(stderr, "cutoff history for (%s);\n",
			h->e->origin->name);
		print_dot_cutoff(h);
	}

	printf("}\n");

	fprintf(stderr, "%d cutoff histories\n\n", num_cutoffs);

	fprintf(stderr, "Histories:\n");

	g_hash_table_iter_init (&iter, unf->events);
	while (g_hash_table_iter_next (&iter, &key, &value)) {
		event_t *ev = (event_t *)value;
		GHashTableIter hiter;
		g_hash_table_iter_init(&hiter, ev->hist);
		while (g_hash_table_iter_next (&hiter, &key, &value)) {
			print_ll_history(stderr, (hist_t*)value);
		}
	}
}
