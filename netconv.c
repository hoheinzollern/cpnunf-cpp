/****************************************************************************/
/* netconv.c                                                                */
/*                                                                          */
/* Functions for creating and modifying Petri net elements		    */
/****************************************************************************/

#include <string.h>
#include "common.h"
#include "netconv.h"
#include "unfold.h"
#include "order.h"

int event_last = 0;
int cond_last = 0;

/**
 * Creates a new net without places or transitions.
 */
net_t* nc_create_net()
{
	net_t *net = MYmalloc(sizeof(net_t));
	net->places = NULL;
	net->transitions = NULL;
	net->numpl = net->numtr = 0;
	return net;
}

guint mark_hash(gconstpointer mvec)
{
	guchar *marking = (guchar *)mvec;
	guint res = 0, i;
	for (i = 1; i < net->numpl; i++) {
		res += marking[i] * i;
#ifdef __DEBUG__
		g_assert(marking[i] == 0 || marking[i] == 1);
#endif
	}
	return res;
}

gboolean mark_equal(gconstpointer v1, gconstpointer v2)
{
	guchar *vec1 = (guchar*)v1, *vec2 = (guchar*)v2, i;
	for (i = 0; i < net->numpl; i++) {
#ifdef __DEBUG__
		g_assert(vec1[i] == 0 || vec1[i] == 1);
		g_assert(vec2[i] == 0 || vec2[i] == 1);
#endif
		if (vec1[i] != vec2[i])
			return FALSE;
	}
	return TRUE;
}

/**
 * Creates an empty unfolding
 */
unf_t* nc_create_unfolding()
{
	unf_t *unf = MYmalloc(sizeof(unf_t));
	unf->markings = g_hash_table_new(mark_hash, mark_equal);
	unf->conditions = g_hash_table_new(NULL, NULL);
	unf->events = g_hash_table_new(NULL, NULL);
	return unf;
}

/**
 * Creates a new place in the given net. The new node has no
 * incoming or outgoing arcs.
 */
place_t* nc_create_place (net_t *net)
{
	place_t *pl = MYmalloc(sizeof(place_t));
	pl->next = net->places;
	net->places = pl;
	pl->preset = pl->postset = pl->conds = NULL;
	pl->num = ++net->numpl;
	return pl;
}

/**
 * Creates a new transition in the given net. The new node has no
 * incoming or outgoing arcs and is unmarked.
 */
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

/**
 * Create an arc between two nodes (place->transition or transition->place)
 */
void nc_create_arc (nodelist_t **fromlist, nodelist_t **tolist,
		   void *from, void *to)
{
	nodelist_t *list;

	for (list = *fromlist; list; list = list->next)
		if (list->node == to) return;

	nodelist_push(fromlist,to);
	nodelist_push(tolist,from);
}

/**
 * compute (maximal) sizes of transition presets/postsets
 */
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
		tr->readarc_size = k;
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
	if (a<b) return -1;
	else return 0;
}

/**
 * Creates a new condition given a place and it's pre-event
 * @arg pl the image for the condition in the original net_t
 * @arg ev the single event in the preset of the condition
 * @return the newly created condition
 */
cond_t *nc_cond_new(place_t *pl, event_t *ev)
{
	struct cond_t *cond = (cond_t*)MYmalloc(sizeof(cond_t));
	cond->num = cond_last++;
	
	cond->pre_ev = ev;
	cond->origin = pl;
	
	cond->postset = array_new(0);
	cond->readarcs = array_new(0);
	
	cond->co_private = g_hash_table_new(NULL, NULL);
	
	return cond;
}

/**
 * Creates an event for the unfolding
 */
event_t *nc_event_new(trans_t *tr, array_t *pre, array_t *read)
{
	event_t *ev = (event_t*)MYmalloc(sizeof(event_t));
	ev->num = event_last++;
	
	ev->origin = tr;
	ev->preset = pre;
	ev->readarcs = read;
	
	// Adds a new condition for each place in the postset:
	array_t *post = ev->postset = array_new(tr->postset_size);
	nodelist_t *ps = tr->postset;
	while (ps) {
		cond_t *cond = nc_cond_new(ps->node, ev);
		array_append(post, cond);
		ps = ps->next;
	}
	array_sort(post);
#ifdef __DEBUG__
	g_assert(array_ordered(post));
#endif

	ev->hist = g_hash_table_new(NULL, NULL);
	
	return ev;
}

int nc_next_cutoff_event()
{
	return event_last++;
}

/**
 * Adds an event and it's postset to the unfolding
 */
void nc_add_event(event_t *ev)
{
	g_hash_table_insert(unf->events, ev, ev);
	int i;
	for (i=0; i<ev->postset->count; i++)
	{
		cond_t *cond = array_get(ev->postset, i);
#ifdef __DEBUG__
		g_assert(cond != NULL);
#endif
		g_hash_table_insert(unf->conditions, cond, cond);
	}
	
	// Update reverse link side
	for (i=0; i<ev->preset->count; i++)
	{
		cond_t *cond = array_get(ev->preset, i);
#ifdef __DEBUG__
		g_assert(cond != NULL);
#endif
		array_insert_ordered(cond->postset, ev);
	}
	for (i=0; i<ev->readarcs->count; i++)
	{
		cond_t *cond = array_get(ev->readarcs, i);
#ifdef __DEBUG__
		g_assert(cond != NULL);
#endif
		array_insert_ordered(cond->readarcs, ev);
	}
}
