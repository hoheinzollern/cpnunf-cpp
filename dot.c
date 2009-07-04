#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"
#include "output.h"

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

void print_dot_cutoff(event_t* ev)
{
	printf("  e%d [label=\"e%d (%s)\" shape=box style=dashed];\n",
		ev->num,ev->num,ev->origin->name);
	int i;
	for (i = 0; i < ev->preset->count; i++)
		printf("  b%d -> e%d;\n",
		       ((cond_t*)array_get(ev->preset, i))->num,
		       ev->num);
	for (i = 0; i < ev->readarcs->count; i++)
		printf("  b%d -> e%d [dir=none];\n",
		       ((cond_t*)array_get(ev->readarcs, i))->num,
		       ev->num);
	for (i = 0; i < ev->postset->count; i++) {
		cond_t *co = ((cond_t*)array_get(ev->postset, i));
		printf("  b%d [label=\"b%d (%s)\" shape=circle];\n",
		       co->num, co->num, co->origin->name);
		printf("  e%d -> b%d;\n", ev->num, co->num);
	}
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
		fprintf(stderr, "cutoff history for e%d (%s);\n",
			h->e->num, h->e->origin->name);
		print_dot_cutoff(h->e);
	}

	printf("}\n");

	fprintf(stderr, "%d cutoff histories\n", num_cutoffs);
}
