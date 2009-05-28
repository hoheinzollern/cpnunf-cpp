/****************************************************************************/
/* netconv.h                                                                */
/*                                                                          */
/* Definitions for netconv.c, readpep.c, nodelist.c, mci.c		    */
/****************************************************************************/

#ifndef __NETCONV_H__
#define __NETCONV_H__

#include <glib.h>

#define COARRAY_TYPE void

typedef unsigned char uchar;

/* If you change these structures, do keep the "next" field at the top;
   reverse_list() depends on it.					    */

typedef struct place_t
{
	struct place_t *next;
	char  *name;			// short name
	int    num;			// number
	struct nodelist_t *preset;	// unordered list of preset
	struct nodelist_t *postset;	// unordered list of postset
	struct nodelist_t *readarcs;	// read arcs (unordered)
	struct nodelist_t *conds;	// conditions derived from this place
	char marked;		 	// non-zero if place is marked
} place_t;

typedef struct trans_t
{
	struct trans_t *next;
	char  *name;			// short name
	int    num;			// number
	struct nodelist_t *preset;	// ordered array of preset
	struct nodelist_t *postset;	// ordered array of postset
	struct nodelist_t *readarcs;	// read arcs (ordered)
	short  preset_size, postset_size, readarc_size;
} trans_t;

typedef struct cond_t
{
	struct cond_t *next;
	struct event_t *pre_ev;		// the single event in the preset
	struct event_t **postset;	// ordered array of postset
	struct event_t **readarcs;	// read arcs (ordered)
	struct place_t *origin;		// associated place
	int    num;			// number (needed by co_relation)
	int    mark;			// used by marking_of
	GHashTable *co_private;		// array of co-conditions
} cond_t;

typedef struct event_t
{
	struct event_t *next;
	struct cond_t **preset;		// array of preset/postset conditions
	struct cond_t **postset;	// size fixed by sizes of origin
	struct cond_t **readarcs;	// read arcs (ordered)
	struct trans_t *origin;		// associated transition
	int    mark;			// used by marking_of
	GHashTable   *co;
	GHashTable   *qco;
	short  foata_level;
	short  preset_size, postset_size;
} event_t;

/**
 * This structure is used to define the list of predecessors for H
 */
typedef struct pred_t {
	struct hist_t *hist;
} pred_t;

/**
 * this structure defines an history as an event plus the list of it's predecessors
 */
typedef struct hist_t {
	int size;			// size of the history
	struct event_t *e;		// last event in history
	struct mark_t *mark;		// marking of the history
	struct pred_t **pred;		// the predecessors
} hist_t;

/**
 * Co-array structure, also used for qco-relation.
 */
typedef struct co_array_t {
	struct cond_t *cond;		// condition in co-array
	struct hist_t **hist;		// array of concurrent histories
} co_array_t;

/**
 * net_t: this structure represents the net
 */
typedef struct
{
	place_t *places;	/* pointer to first place		*/
	trans_t *transitions;	/* pointer to first transition		*/ 
	int numpl, numtr;	/* number of places/transitions in net	*/
	int maxpre, maxpost;	/* maximal size of a t-pre/postset	*/
	int maxra;		/* maximum readarcs of transitions      */
} net_t;

/**
 * unf_t: this structure represents the unfolding
 */
typedef struct
{
	cond_t *conditions;	/* pointer to first condition		*/
	event_t *events;	/* pointer to first event		*/ 
	int numco, numev;	/* number of conditions/events in net	*/
	struct nodelist_t *m0;	/* list of minimal conditions		*/
} unf_t;

/****************************************************************************/

extern net_t* nc_create_net ();
extern unf_t* nc_create_unfolding ();
extern place_t* nc_create_place (net_t*);
extern trans_t* nc_create_transition (net_t*);
extern void nc_create_arc (struct nodelist_t**,struct nodelist_t**,void*,void*);
extern void nc_compute_sizes (net_t*);
extern void nc_static_checks (net_t*,char*);

/*****************************************************************************/
/* declarations from nodelist.c						     */

typedef struct nodelist_t
{
	void   *node;
	struct nodelist_t* next;
} nodelist_t;

extern nodelist_t* nodelist_alloc ();
extern nodelist_t* nodelist_push (nodelist_t**list,void*);
extern nodelist_t* nodelist_insert (nodelist_t**,void*e);
extern void nodelist_delete (nodelist_t*);
extern char nodelist_compare (nodelist_t*, nodelist_t*);

/****************************************************************************/
/* declarations for readpep.c						    */

extern net_t* read_pep_net(char*);

/****************************************************************************/
/* declarations for dot.c						    */

extern void write_dot_output (unf_t*, nodelist_t*, char);
extern void* reverse_list (void*);

#endif
