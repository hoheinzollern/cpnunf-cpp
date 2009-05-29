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

typedef struct nodelist_t
{
	void   *node;
	struct nodelist_t* next;
} nodelist_t;

/**
 * If you change these structures, do keep the "next" field at the top;
 * reverse_list() depends on it.
 */

typedef struct place_t
{
	struct place_t *next;
	char  *name;			// short name
	int    num;			// number
	nodelist_t *preset;	// unordered list of preset
	nodelist_t *postset;	// unordered list of postset
	nodelist_t *readarcs;	// read arcs (unordered)
	nodelist_t *conds;	// conditions derived from this place
	char marked;		 	// non-zero if place is marked
} place_t;

typedef struct trans_t
{
	struct trans_t *next;
	char  *name;			// short name
	int    num;			// number
	nodelist_t *preset;	// ordered array of preset
	nodelist_t *postset;	// ordered array of postset
	nodelist_t *readarcs;	// read arcs (ordered)
	short  preset_size, postset_size, readarc_size;
} trans_t;

/**
 * This structure defines an history as an event plus the list of it's predecessors;
 * note that such definition for an history is equivalent to an enriched event.
 */
typedef struct hist_t {
	int size;			// size of the history
	struct event_t *e;		// last event in history
	struct mark_t *mark;		// marking of the history
	struct pred_t **pred;		// the predecessors, ordered by b
} hist_t;

#define HIST_R 0x01
#define HIST_C 0x02

/**
 * This structure is used to define the list of predecessors for H
 */
typedef struct pred_t {
	uchar flag;		// marks the type of history chosen
	struct cond_b *cond;
	struct hist_t *hist;
} pred_t;

typedef struct cond_t
{
	struct event_t *pre_ev;		// the single event in the preset
	GArray *postset;		// ordered array of postset
	GArray *readarcs;	// read arcs (ordered)
	place_t *origin;		// associated place
	int num;			// number (needed by co_relation)
	int mark;			// used by marking_of
	GHashTable *co_private;		// array of co-conditions
} cond_t;

typedef struct event_t
{
	GArray *preset;		// array of preset/postset conditions
	GArray *postset;		// size fixed by sizes of origin
	GArray *readarcs;	// read arcs (ordered)
	trans_t *origin;		// associated transition
	int num;
	int mark;			// used by marking_of
	GHashTable   *co;
	GHashTable   *qco;
	short  foata_level;
	GHashTable *hist;
} event_t;

/**
 * Co-array structure, also used for qco-relation.
 */
typedef struct co_cond_t {
	cond_t *cond;		// condition in co-array
	short hists_len;
	hist_t **hists;		// array of concurrent histories
} co_cond_t;

typedef struct co_t {
	int len;
	struct co_cond_t *conds;
} co_t;

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
	GHashTable *markings;
	GHashTable *conditions;	/* pointer to first condition		*/
	GHashTable *events;	/* pointer to first event		*/
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
