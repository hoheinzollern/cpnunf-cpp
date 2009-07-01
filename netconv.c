/****************************************************************************/
/* netconv.c                                                                */
/*                                                                          */
/* Functions for creating and modifying Petri net elements		    */
/****************************************************************************/

#include <string.h>
#include "common.h"
#include "netconv.h"
#include "unfold.h"

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

guint mark_hash(gconstpointer pvec)
{
	parikh_vec_t *parikh = (parikh_vec_t *)pvec;
	guint res1 = 0, res2 = 0, i;
	for (i = 0; i < parikh->size; i++) {
		res1 += parikh->parikh[i].appearances;
		res2 += parikh->parikh[i].tr_num;
	}
	return res1 + res2;
}

gboolean mark_equal(gconstpointer v1, gconstpointer v2)
{
	int i;
	parikh_vec_t *vec1 = (parikh_vec_t*)v1,
		*vec2 = (parikh_vec_t*)v2;
	gboolean res = vec1->size==vec2->size;
	for (i = 0; res && i < vec1->size; i++) {
		res = (vec1->parikh[i].tr_num == vec2->parikh[i].tr_num) &&
		      (vec1->parikh[i].appearances == vec2->parikh[i].appearances);
	}
	return res;
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
	g_assert(array_ordered(post));
	
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
	g_hash_table_insert(unf->events, ev, ev);
	int size = ev->postset->len, i;
	for (i=0; i<size; i++)
	{
		cond_t *cond = array_get(ev->postset, i);
		g_hash_table_insert(unf->conditions, cond, cond);
	}
	
	// Update reverse link side
	for (i=0; i<ev->preset->len; i++)
	{
		cond_t *cond = array_get(ev->preset, i);
		array_insert_ordered(cond->postset, ev);
	}
	for (i=0; i<ev->readarcs->len; i++)
	{
		cond_t *cond = array_get(ev->readarcs, i);
		array_insert_ordered(cond->readarcs, ev);
	}
}
