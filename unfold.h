/****************************************************************************/
/* unfold.h								    */
/*                                                                          */
/* Definitions for unfold.c, marking.c, pe.c, order.c			    */
/****************************************************************************/

#ifndef __UNFOLD_H__
#define __UNFOLD_H__

#include <stdlib.h>
#include "netconv.h"

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

extern void unfold();	/* the unfolding procedure */


/***************************************************************************/
/* declarations for order.c						   */

typedef struct parikh_t
{
	unsigned short int tr_num;
	unsigned short int appearances;
} parikh_t;

#endif
