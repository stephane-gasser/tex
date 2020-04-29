#include "geqdefine.h"
#include "eqdestroy.h"

void geqdefine(halfword p, quarterword t, halfword e)
{
	eqdestroy(eqtb[p]);
	subtype(p) = 1;
	type(p) = t;
	eqtb[p].hh.rh = e;
}
