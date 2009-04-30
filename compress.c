#include "common.h"
#include "netconv.h"
#include "unfold.h"

unf_t *c_unf;
nodelist_t *c_cutoffs;

void compress_unfolding ()
{
	cond_t *co, *c_co;
	event_t *ev, *c_ev;

	nodelist_t *backup_cutoffs = cutoff_list;
	nodelist_t *backup_corrs = corr_list;
	nodelist_t *list;

	int i = 0;

	unf->conditions = reverse_list(unf->conditions);
	unf->events = reverse_list(unf->events);

	marking_init();

	/* match transitions and events with the same phantoms */
	for (ev = unf->events; ev; ev = ev->next)
	{
		nodelist_t *marking = NULL;

		cutoff_list = corr_list = NULL;
		nodelist_insert(&marking,ev->origin);
		for (i = 0; i < ev->preset_size; i++)
			nodelist_insert(&marking,ev->preset[i]->phantom);
		add_marking(marking,ev);

		if (cutoff_list)
		{
			event_t *evcorr = (event_t*)(corr_list->node);
			nodelist_delete(cutoff_list);
			nodelist_delete(corr_list);

			ev->phantom = evcorr? evcorr->phantom : NULL;
			for (i = 0; i < ev->postset_size; i++)
				ev->postset[i]->phantom
					= evcorr->postset[i]->phantom;
		}
		else
			ev->phantom = ev;
	}

	/* generate compressed unfolding */
	c_unf = nc_create_unfolding();
	c_cutoffs = NULL;

	c_unf->m0 = NULL;
	for (list = unf->m0; list; list = list->next)
		nodelist_push(&(c_unf->m0),(co = list->node));

	/* compressed conditions */
	for (co = unf->conditions; co; co = co->next)
	{
		if (co != co->phantom) continue;

		c_co = MYmalloc(sizeof(cond_t));
		c_co->next = c_unf->conditions;
		c_unf->conditions = c_co;
		co->compressed = c_co;

		c_co->num = c_unf->numco++;
		c_co->origin = co->origin;
		c_co->phantom = c_co;
	}

	/* compressed events */
	for (ev = unf->events; ev; ev = ev->next)
	{
		if (ev != ev->phantom) continue;

		c_ev = MYmalloc(sizeof(cond_t));
		c_ev->next = c_unf->events;
		c_unf->events = c_ev;
		ev->compressed = c_ev;

		c_ev->mark = c_unf->numev++;
		c_ev->origin = ev->origin;
		c_ev->preset_size = ev->preset_size;
		c_ev->postset_size = ev->postset_size;
		c_ev->phantom = c_ev;
	}

	/* compressed cutoffs */
	for (list = backup_cutoffs; list; list = list->next)
	{
		ev = list->node;
		if (ev != ev->phantom) continue;
		nodelist_push(&(c_cutoffs),ev->compressed);
	}

	/* generate compressed arcs */
	for (co = unf->conditions; co; co = co->next)
	{
		if (co != co->phantom) continue;

		c_co = co->compressed;
		c_co->pre_ev = co->pre_ev? co->pre_ev->phantom->compressed
					 : NULL;
		c_co->postset = NULL;
		for (list = co->postset; list; list = list->next)
		{
			ev = list->node;
			nodelist_push(&(c_co->postset),ev->phantom->compressed);
		}
	}
	for (ev = unf->events; ev; ev = ev->next)
	{
		if (ev != ev->phantom) continue;

		c_ev = ev->compressed;

		c_ev->preset = MYmalloc(ev->preset_size * sizeof(cond_t*));
		for (i = 0; i < ev->preset_size; i++)
			c_ev->preset[i] = ev->preset[i]->phantom->compressed;

		c_ev->postset = MYmalloc(ev->postset_size * sizeof(cond_t*));
		for (i = 0; i < ev->postset_size; i++)
			c_ev->postset[i] = ev->postset[i]->phantom->compressed;
	}

	/* restore variables */
	unf->conditions = reverse_list(unf->conditions);
	unf->events = reverse_list(unf->events);

	cutoff_list = backup_cutoffs;
	corr_list = backup_corrs;
}
