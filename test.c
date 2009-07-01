#include "test.h"
#include "glib.h"

void check_co(co_t *co)
{
	int i;
	for (i = 0; i < co->len; i++)
		check_co_cond(co->conds + i);
}

void check_co_cond(co_cond_t *cond)
{
		g_assert(cond->cond!=NULL);
		g_assert(cond->hists_len>0);
		g_assert(cond->hists!=NULL);
}
