/****************************************************************************/
/* common.h								    */
/*									    */
/* Definitions for common.c						    */
/****************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>

#define PROGRAM_NAME "unfold"

extern void* MYmalloc(size_t);
extern void* MYcalloc(size_t);
extern void* MYrealloc(void*,size_t);
extern char* MYstrdup(char*);

/**
 * Outputs an error message to stderr and exits.
 */
extern void nc_error (const char*,...);

/**
 * nc_warning
 * Emits a warning, but doesn't terminate.
 */
extern void nc_warning (const char*,...);

#endif
