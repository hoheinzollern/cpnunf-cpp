/****************************************************************************/
/* unfold.h								    */
/*                                                                          */
/* Definitions for unfold.c, marking.c, pe.c, order.c			    */
/****************************************************************************/

#ifndef __UNFOLD_H__
#define __UNFOLD_H__

#include <stdlib.h>
#include "netconv.h"
#include "order.h"

/****************************************************************************/
/* declarations from unfold.c						    */

extern net_t *net;	/* stores the net	*/
extern unf_t *unf;	/* stores the unfolding */

extern int conditions_size, events_size;
extern int ev_mark;		  	   /* needed for various procedures */
extern event_t **events;

extern int exitcode;		/* proposed exit code of the program         */
extern trans_t *stoptr;		/* the transition mentioned by the -T switch */

extern nodelist_t *cutoff_list, *corr_list;  /* cut-off/corresponding list */
extern nodelist_t *c_cutoffs;	/* cutoff list for c_unf */

extern co_t *co_new(int size);
extern co_t *co_array_new(int n);
extern co_t *co_copy(co_t *orig);
extern void co_finalize(co_t *co);
extern void co_array_finalize(co_t *co, int n);
extern void co_insert(co_t *co, cond_t *cond, hist_t *hist);
extern void co_insert_co_cond(co_t *co, co_cond_t *cond);

extern event_t *get_or_create_event(hist_t *hist, UNFbool *created);

extern void unfold();	/* the unfolding procedure */

#endif
