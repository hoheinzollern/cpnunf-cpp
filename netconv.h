/****************************************************************************/
/* netconv.h                                                                */
/*                                                                          */
/* Definitions for netconv.c, readpep.c, nodelist.c, mci.c		    */
/****************************************************************************/

#ifndef __NETCONV_H__
#define __NETCONV_H__

#include <glib.h>
#include "common.h"

#define COARRAY_TYPE void

#define HAS_FLAG(flags, flag) (((flags) & (flag)) == (flag))

#define SET_FLAG(flags, flag) ((flags) = (((flags) & ~(flag)) | (flag)))

#define CLEAN_FLAG(flags, flag) ((flags) = ((flags) & ~(flag)))

#define CLEAR_FLAGS(flags) ((flags) = 0)

#define HIST_R 0x01
#define HIST_C 0x02

#define PRESET 0x04
#define CONTEXT 0x08

#define BLACK 0x10

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

/**
 * This structure represents a place in the original c-net
 */
typedef struct place_t
{
	/// Pointer to the next place in the list of places
	struct place_t *next;
	
	/// Short name for the place
	char  *name;
	
	/// Number
	unsigned short int num;
	
	/// unordered list of preset
	nodelist_t *preset;
	
	/// unordered list of postset
	nodelist_t *postset;
	
	/// read arcs (unordered)
	nodelist_t *readarcs;
	
	/// conditions derived from this place
	nodelist_t *conds;
	
	/// non-zero if place is marked
	char marked;
} place_t;

typedef struct trans_t
{
	/// Pointer to the next event in the list of events
	struct trans_t *next;
	
	/// Short name for the event
	char  *name;
	
	/// Number
	unsigned short int num;
	
	/// unordered list of preset
	nodelist_t *preset;
	
	/// unordered list of postset
	nodelist_t *postset;
	
	/// read arcs (unordered)
	nodelist_t *readarcs;
	
	/// Size of preset, postset and read arcs
	short  preset_size, postset_size, readarc_size;
} trans_t;

/**
 * This structure defines an history as an event plus the list of it's predecessors;
 * note that such definition for an history is equivalent to an enriched event.
 */
typedef struct hist_t {
	/// size of the history
	int size;
	
	/// last event in history
	struct event_t *e;
	
	/// parikh vector of the history
	struct parikh_t *parikh;

	/// marking of the history
	guchar *marking;
	
	/// the predecessors, ordered by b
	struct pred_t *pred;
	
	/// the number of predecessors
	int pred_n;
	
	/// needed to compute the cardinality
	unsigned char flags;

	struct co_t *co;
} hist_t;

/**
 * This structure is used to define the list of predecessors for H
 */
typedef struct pred_t {
	/// marks the type of history chosen
	unsigned char flags;
	
	/// condition form which the history was chosen
	struct cond_t *cond;
	
	/// the chosen history
	struct hist_t *hist;
} pred_t;

/**
 * Defines a condition in the unfolding
 */
typedef struct cond_t
{
	/// the single event in the preset
	struct event_t *pre_ev;
	
	/// ordered array of postset
	struct array_t *postset;
	
	/// read arcs (ordered)
	struct array_t *readarcs;
	
	/// associated place
	place_t *origin;
	
	/// number (needed by co_relation)
	int num;
	
	/// used by marking_of
	int mark;
	
	/// array of co-conditions
	GHashTable *co_private;
} cond_t;

/**
 * Defines an event in the unfolding
 */
typedef struct event_t
{
	/// array of preset/postset conditions
	struct array_t *preset;
	
	/// size fixed by sizes of origin
	struct array_t *postset;
	
	/// read arcs (ordered)
	struct array_t *readarcs;
	
	/// associated transition
	trans_t *origin;
	
	/// number (needed by co_relation)
	int num;
	
	/// used by marking_of
	int mark;
	
	/// Foata level for the event
	short  foata_level;
	
	/// hash table of the histories associated to this event
	GHashTable *hist;
} event_t;

/**
 * Co-array structure, also used for qco-relation.
 */
typedef struct co_cond_t {
	/// condition in co-array
	cond_t *cond;
	
	/// length of the hists array
	int hists_len;
	
	/// array of histories concurrent to cond
	hist_t **hists;
} co_cond_t;

typedef struct co_t {
	/// number of concurrent conditions
	int len;
	
	/// pointer to the first condition
	struct co_cond_t *conds;
} co_t;

/**
 * net_t: this structure represents the net
 */
typedef struct net_t
{
	place_t *places;	/** pointer to first place		*/
	trans_t *transitions;	/** pointer to first transition		*/
	int numpl, numtr;	/** number of places/transitions in net	*/
	int maxpre, maxpost;	/** maximal size of a t-pre/postset	*/
	int maxra;		/** maximum readarcs of transitions      */
} net_t;

/**
 * unf_t: this structure represents the unfolding
 */
typedef struct unf_t
{
	GHashTable *markings;
	GHashTable *conditions;
	GHashTable *events;
	struct nodelist_t *m0;	/* list of minimal conditions		*/
	event_t *root;		// root event, not part of the unfolding
} unf_t;

/****************************************************************************/

extern net_t* nc_create_net ();
extern unf_t* nc_create_unfolding ();
extern place_t* nc_create_place (net_t*);
extern trans_t* nc_create_transition (net_t*);
extern void nc_create_arc (struct nodelist_t**,struct nodelist_t**,void*,void*);
extern void nc_compute_sizes (net_t*);
extern void nc_static_checks (net_t*,char*);
extern cond_t *nc_cond_new(place_t *pl, event_t *ev);
extern event_t *nc_event_new(trans_t *tr, array_t *pre, array_t *read);
extern int nc_next_cutoff_event();
extern void nc_add_event(event_t *ev);

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

#endif
