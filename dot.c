#include <stdio.h>
#include <string.h>

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

void print_event(event_t *evt)
{
	printf("  e%d [shape=box]\n");
}

void write_dot_output (unf_t *u, nodelist_t *cutoffs, char compressed)
{
	cond_t *co;
	event_t *ev;
	place_t *pl;
	nodelist_t *list, *list2;

	int i, ev_num = 0;

	for (ev = u->events; ev; ev = ev->next)
		ev->mark = ++ev_num;
	
	printf("digraph test {\n");

	for (co = u->conditions; co; co = co->next)
		printf("  c%d [label=\"%s (c%d)\" shape=circle];\n",
				co->num,co->origin->name,co->num);
	
	for (ev = u->events; ev; ev = ev->next)
                printf("  e%d [label=\"%s (e%d)\" shape=box];\n",
			ev->mark,ev->origin->name,ev->mark);

	for (ev = u->events; ev; ev = ev->next)
	{
		for (i = 0; i < ev->preset_size; i++)
		{
			co = ev->preset[i];
			printf("  c%d -> e%d",co->num,ev->mark);
			if (compressed)
				for (list2 = ev->origin->readarcs; list2;
					list2 = list2->next)
				    if ((pl = list2->node) == co->origin)
					    printf(" [dir=none]");
			printf(";\n");
		}

		for (i = 0; i < ev->postset_size; i++)
		{
			co = ev->postset[i];
			for (list2 = ev->origin->readarcs; list2;
					list2 = list2->next)
				if ((pl = list2->node) == co->origin)
					break;
			if (!list2 || !compressed)
				printf("  e%d -> c%d;\n",ev->mark,co->num);
		}
	}

	int num_cutoffs = 0;
	for (list = cutoffs; list; list = list->next)
	{
		num_cutoffs++;
		printf("  e%d [style=dashed];\n",(ev = list->node)->mark);
	}

	fprintf(stderr,"%d event%s (%d cutoff%s)\n",
			ev_num,(ev_num == 1)? "" : "s",
			num_cutoffs,(num_cutoffs == 1)? "" : "s");

	printf("}\n");
}
