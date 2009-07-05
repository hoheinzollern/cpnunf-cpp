#include "test.h"
#include "glib.h"

void check_co(co_t *co)
{
	int i;
	for (i = 0; i < co->len; i++)
		check_co_cond(co->conds + i);
	for (i = 0; i < co->len-1; i++)
		g_assert(co->conds[i].cond < co->conds[i+1].cond);
}

void check_co_cond(co_cond_t *cond)
{
		g_assert(cond->cond!=NULL);
		g_assert(cond->hists_len>0);
		g_assert(cond->hists!=NULL);
}
