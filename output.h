#ifndef OUTPUT_H
#define OUTPUT_H
#include "array.h"

// dot.c

/**
  * Outputs the unfolding in dot format. Discards histories.
  * @arg unf the unfolding
  * @arg cutoffs the list of cutoffs
  */
extern void write_dot_output(unf_t* unf, nodelist_t* cutoffs);

// ll_net.c
/**
  * Outputs the unfolding in ll_net format with the extension of read arcs.
  * Optionally appends the information on histories.
  * @arg unf the unfolding
  * @arg cutoffs the list of cutoffs
  * @arg hist TRUE if you want histories, FALSE otherwise.
  */
extern void write_ll_net(unf_t* unf, nodelist_t* cutoffs,
			 UNFbool hist);

extern void print_ll_history(FILE *stream, hist_t *h);

#endif
