#include "patch.h"

guint pred_hash(gconstpointer v)
{
	return  g_direct_hash(((pred_t *)v)->cond) +
			g_direct_hash(((pred_t *)v)->hist);
}

gboolean pred_equal(gconstpointer v1, gconstpointer v2)
{
	return  (((pred_t *)v1)->cond == ((pred_t *)v2)->cond) &&
			(((pred_t *)v1)->hist == ((pred_t *)v2)->hist);
}

void build_subsumed(GHashTable *tbl, pred_t *p)
{
	int i;
	for (i = 0; i < p->hist->pred_n; i++) {
		if (HAS_FLAG(p->hist->pred[i].flags, CONTEXT) && HAS_FLAG(p->hist->pred[i].flags, HIST_C)
			&& p->hist->pred[i].cond == p->cond) {

			pair_t *pr = MYmalloc(sizeof(pair_t));
			pr->origin = p;
			pr->produced = p->hist->pred + i;

			pred_t *pred = g_hash_table_lookup(tbl, p);
			if (!pred) {
				g_hash_table_insert(tbl, p, pr);
				pred = p;
			}

			if (!HAS_FLAG(pred->flags, BLACK))
				SET_FLAG(pred->flags, RED);
		} else if (HAS_FLAG(p->hist->pred[i].flags, PRESET)) {
			pair_t *pr = g_hash_table_lookup(tbl, p->hist->pred + i);
			if (pr) {
				CLEAN_FLAG(pr->produced->flags, RED);
				SET_FLAG(pr->produced->flags, BLACK);
			}
		}
		build_subsumed(tbl, p->hist->pred + i);
	}
}

void clean_pred(void *v)
{
	CLEAN_FLAG(((pred_t*)v)->flags, RED);
	CLEAN_FLAG(((pred_t*)v)->flags, BLACK);
}
