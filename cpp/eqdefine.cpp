#include "eqdefine.h"
#include "eqdestroy.h"
#include "eqsave.h"

void eqdefine(halfword p, quarterword t, halfword e)
{
	if (eq_level(p) == curlevel)
		eqdestroy(eqtb[p]);
	else 
		if (curlevel > 1)
			eqsave(p, eq_level(p));
	eq_level(p) = curlevel;
	eq_type(p) = t;
	equiv(p) = e;
}
