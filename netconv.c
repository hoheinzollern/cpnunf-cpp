/****************************************************************************/
/* netconv.c                                                                */
/*                                                                          */
/* Functions for creating and modifying Petri net elements		    */
/****************************************************************************/

#include <string.h>
#include "common.h"
#include "netconv.h"
#include "unfold.h"

int event_last = -1;
int cond_last = 0;

/****************************************************************************/
/* nc_create_net							    */
/* Creates a new net without places or transitions.			    */

net_t* nc_create_net()
{
	net_t *net = MYmalloc(sizeof(net_t));
	net->places = NULL;
	net->transitions = NULL;
	net->numpl = net->numtr = 0;
	return net;
}

unf_t* nc_create_unfolding()
{
	unf_t *unf = MYmalloc(sizeof(unf_t));
	unf->conditions = g_hash_table_new(NULL, NULL);
	unf->events = g_hash_table_new(NULL, NULL);
	return unf;
}

/****************************************************************************/
/* nc_create_{place,transition}						    */
/* Creates a new place or transition in the given net. The new node has no  */
/* incoming or outgoing arcs and is unmarked.				    */

place_t* nc_create_place (net_t *net)
{
	place_t *pl = MYmalloc(sizeof(place_t));
	pl->next = net->places;
	net->places = pl;
	pl->preset = pl->postset = pl->conds = NULL;
	pl->num = ++net->numpl;
	return pl;
}

trans_t* nc_create_transition (net_t *net)
{
	trans_t *tr = MYmalloc(sizeof(trans_t));
	tr->next = net->transitions;
	net->transitions = tr;
	tr->preset = tr->postset = NULL;
	tr->preset_size = 0;
	tr->num = ++net->numtr;
	return tr;
}

/****************************************************************************/
/* nc_create_arc							    */
/* Create an arc between two nodes (place->transition or transition->place) */

void nc_create_arc (nodelist_t **fromlist, nodelist_t **tolist,
		   void *from, void *to)
{
	nodelist_t *list;

	for (list = *fromlist; list; list = list->next)
		if (list->node == to) return;

	nodelist_push(fromlist,to);
	nodelist_push(tolist,from);
}

/****************************************************************************/
/* nc_compute_sizes							    */
/* compute (maximal) sizes of transition presets/postsets		    */

void nc_compute_sizes (net_t *net)
{
	trans_t *tr;
	int k;

	net->maxpre = net->maxpost = net->maxra = 0;
	for (tr = net->transitions; tr; tr = tr->next)
	{
		nodelist_t *list;

		for (k = 0, list = tr->preset; list; k++, list = list->next);
		tr->preset_size = k;
		if (net->maxpre < k) net->maxpre = k;

		for (k = 0, list = tr->postset; list; k++, list = list->next);
		tr->postset_size = k;
		if (net->maxpost < k) net->maxpost = k;

		for (k = 0, list = tr->readarcs; list; k++, list = list->next);
		if (net->maxra < k) net->maxra = k;
	}
}

/*****************************************************************************/

void nc_static_checks (net_t* net, char *stoptr_name)
{
	place_t *pl;
	trans_t *tr;

	for (tr = net->transitions; tr; tr = tr->next)
	{
		if (!tr->preset || !tr->postset)
			nc_warning("%s is not restricted",tr->name);
		if (stoptr_name && !strcmp(tr->name,stoptr_name))
			stoptr = tr;
	}

	if (stoptr_name && !stoptr)
		nc_error("Transition %s not found",stoptr_name);

	for (pl = net->places; pl; pl = pl->next)
		if (pl->marked) break;
	if (!pl) nc_error("no initial marking");
}

gint nc_compare(gconstpointer a, gconstpointer b)
{
	if (a>b) return 1;
	if (a==b) return 0;
	if (a<b) return -1;
}

/**
 * Creates a new condition given a place and it's pre-event
 */
cond_t *nc_cond_new(place_t *pl, event_t *ev)
{
	struct cond_t *cond = (cond_t*)MYmalloc(sizeof(cond_t));
	cond->num = cond_last++;
	
	cond->pre_ev = ev;
	cond->origin = pl;
	
	cond->postset = g_array_new(FALSE, TRUE, sizeof(event_t *));
	cond->readarcs = g_array_new(FALSE, TRUE, sizeof(event_t *));
	
	cond->co_private = g_hash_table_new(NULL, NULL);
	
	return cond;
}

/**
 * Creates an event for the unfolding
 */
event_t *nc_event_new(trans_t *tr, GArray *pre, GArray *read)
{
	event_t *ev = (event_t*)MYmalloc(sizeof(event_t));
	ev->num = event_last++;
	
	ev->origin = tr;
	ev->preset = pre;
	ev->readarcs = read;
	
	// Adds a new condition for each place in the postset:
	GArray *post = ev->postset = g_array_new(FALSE, FALSE,
		sizeof(cond_t *));
	// TODO: alternativa: g_array_sized_new con dimensione tr->postset_size
	nodelist_t *ps = tr->postset;
	while (ps) {
		cond_t *cond = nc_cond_new(ps->node, ev);
		g_array_append_val(post, cond);
		ps = ps->next;
	}
	g_array_sort(post, nc_compare);
	
	ev->co = g_hash_table_new(NULL, NULL);
	ev->qco = g_hash_table_new(NULL, NULL);
	ev->hist = g_hash_table_new(NULL, NULL);
	
	return ev;
}

/**
 * Adds an event and it's postset to the unfolding
 */
void nc_add_event(event_t *ev)
{
	g_hash_table_insert(unf->conditions, ev, ev);
	int size = ev->postset->len, i;
	for (i=0; i<size; i++)
	{
		cond_t *cond = g_array_index(ev->postset, cond_t *, i);
		g_hash_table_insert(unf->events, cond, cond);
	}
}