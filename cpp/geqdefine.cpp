#include "geqdefine.h"
#include "eqdestroy.h"

void geqdefine(halfword p, quarterword t, halfword e)
{
	eqdestroy(eqtb[p]);
	eqtb[p].hh.b1 = 1;
	eqtb[p].hh.b0 = t;
	eqtb[p].hh.rh = e;
}
