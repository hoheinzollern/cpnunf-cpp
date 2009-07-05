#ifndef MARKING_H
#define MARKING_H

#include "netconv.h"

nodelist_t* marking_initial ();
int add_marking (nodelist_t *marking, event_t *ev);
int marking_hash (nodelist_t *marking);
void marking_init ();

#endif
