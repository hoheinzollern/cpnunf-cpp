#include "test.h"
#include "glib.h"

void check_co(co_t *co)
{
	int i;
	for (i = 0; i < co->len; i++) {
		g_assert(co->conds[i].hists!=NULL);
		g_assert(co->conds[i].hists!=NULL);
	}
}
