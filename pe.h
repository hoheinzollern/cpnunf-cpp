#ifndef PE_H
#define PE_H
#include "netconv.h"

extern void pe_init ();
extern hist_t* pe_pop ();
extern void pe (hist_t *);
extern UNFbool hist_c(hist_t *, cond_t *);

#endif
