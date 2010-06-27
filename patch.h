#ifndef NETCONV_H
#define NETCONV_H

#include "netconv.h"
#include <glib.h>

typedef struct pair_t {
	pred_t *origin;
	pred_t *produced;
} pair_t;

extern void build_subsumed(GHashTable *tbl, pred_t *p);
extern guint pred_hash(gconstpointer v);
extern gboolean pred_equal(gconstpointer v1, gconstpointer v2);
extern void clean_pred(void *v);

#endif
