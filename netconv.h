/****************************************************************************/
/* netconv.h                                                                */
/*                                                                          */
/* Definitions for netconv.c, readpep.c, nodelist.c, mci.c		    */
/****************************************************************************/

#ifndef __NETCONV_H__
#define __NETCONV_H__

/****************************************************************************/

typedef unsigned char uchar;

/****************************************************************************/
/* structures for places, transitions, conditions, events		    */

/* If you change these structures, do keep the "next" field at the top;
   reverse_list() depends on it.					    */

typedef struct place_t
{
	struct place_t *next;
	char  *name;		    /* short name			    */
	int    num;		    /* number				    */
	struct nodelist_t *preset;  /* unordered list of preset		    */
	struct nodelist_t *postset; /* unordered list of postset	    */
	struct nodelist_t *readarcs; /* read arcs (unordered) */
	struct nodelist_t *conds;   /* conditions derived from this place   */
	char marked;		    /* non-zero if place is marked	    */
} place_t;

typedef struct trans_t
{
	struct trans_t *next;
	char  *name;		    /* short name			    */
	int    num;		    /* number				    */
	struct nodelist_t *preset;  /* unordered list of preset		    */
	struct nodelist_t *postset; /* unordered list of postset	    */
	struct nodelist_t *readarcs; /* read arcs (unordered) */
	short  preset_size, postset_size, readarc_size;
} trans_t;

typedef struct cond_t
{
	struct cond_t *next;
	struct event_t *pre_ev;	    /* the single event in the preset	    */
	struct nodelist_t *postset; /* unordered list of postset	    */
	struct place_t *origin;	    /* associated place			    */
	int    num;		    /* number (needed by co_relation)	    */
	int    mark;		    /* used by marking_of		    */
	int   *coarray_common;	    /* list of co-conditions		    */
	int   *coarray_private;     /* list of co-conditions		    */
	struct cond_t *phantom;	    /* cheat: pointer back to "real" cond   */
	struct cond_t *compressed;  /* corresponding condition in c_unf	    */
} cond_t;

typedef struct event_t
{
	struct event_t *next;
	struct cond_t **preset;	    /* array of preset/postset conditions   */
	struct cond_t **postset;    /* size fixed by sizes of origin	    */
	struct trans_t *origin;	    /* associated transition		    */
	int    mark;		    /* used by marking_of		    */
	int   *coarray;
	short  foata_level;
	short  preset_size, postset_size;
	struct event_t *phantom;
	struct event_t *compressed;
} event_t;

/****************************************************************************/
/* structures for net and unfolding					    */

typedef struct
{
	place_t *places;	/* pointer to first place		*/
	trans_t *transitions;	/* pointer to first transition		*/ 
	int numpl, numtr;	/* number of places/transitions in net	*/
	int maxpre, maxpost;	/* maximal size of a t-pre/postset	*/
	int maxra;		/* maximum readarcs of transitions      */
} net_t;

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

/****************************************************************************/
/* declarations for compress.c						    */

extern void compress_unfolding ();

#endif
