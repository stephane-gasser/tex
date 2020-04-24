#include "eqdefine.h"
#include "eqdestroy.h"
#include "eqsave.h"

void eqdefine(halfword p, quarterword t, halfword e)
{
	if (eqtb[p].hh.b1 == curlevel)
		eqdestroy(eqtb[p]);
	else 
		if (curlevel > 1)
			eqsave(p, eqtb[p].hh.b1);
	eqtb[p].hh.b1 = curlevel;
	eqtb[p].hh.b0 = t;
	eqtb[p].hh.rh = e;
}
