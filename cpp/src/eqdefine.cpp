#include "eqdefine.h"
#include "eqdestroy.h"
#include "sauvegarde.h"
#include "geqdefine.h"

void define(int a, halfword p, quarterword t, halfword e)
{
	if (a >= 4)
		geqdefine(p, t, e);
	else 
		eqdefine(p, t, e);
}

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
