#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"

void* reverse_list (void *ptr)
{
	place_t *newlist = NULL, *list = ptr;

	while (list)
	{
		place_t *tmp = list->next;
		list->next = newlist;
		newlist = list;
		list = tmp;
	}

	return newlist;
}

void print_event(event_t *ev)
{
	printf("  e%d [label=\"%s (e%d)\" shape=box];\n",
		ev->mark,ev->origin->name,ev->mark);
}

void print_readarcs(cond_t *co)
{
	array_t *array = co->readarcs;
	event_t *ev = NULL;
	int i;
	for (i=0; i<array->len; i++) {
		ev = (event_t *)array_get(array, i);
		printf("  c%d -> e%d [dir=none];\n", co->num, ev->mark);
	}
}

void print_postset(cond_t *co)
{
	array_t *array = co->postset;
	event_t *ev = NULL;
	int i;
	for (i=0; i<array->len; i++) {
		ev = (event_t *)array_get(array, i);
		printf("  e%d -> c%d;\n", ev->mark, co->num);
	}
}

void print_condition(cond_t *co)
{
	printf("  c%d [label=\"%s (c%d)\" shape=circle];\n",
			co->num,co->origin->name,co->num);
	print_postset(co);
	print_readarcs(co);
}

void write_dot_output (unf_t *u, nodelist_t *cutoffs)
{
	event_t *ev;
	nodelist_t *list;

	GHashTableIter iter;
	gpointer key, value;

	printf("digraph test {\n");

	g_hash_table_iter_init (&iter, unf->events);
	while (g_hash_table_iter_next (&iter, &key, &value))
		print_event((event_t *)value);

	g_hash_table_iter_init (&iter, unf->conditions);
	while (g_hash_table_iter_next (&iter, &key, &value)) 
		print_condition((cond_t *)value);

	int num_cutoffs = 0;
	for (list = cutoffs; list; list = list->next)
	{
		num_cutoffs++;
		printf("  e%d [style=dashed];\n",(ev = list->node)->mark);
	}

	printf("}\n");
}
