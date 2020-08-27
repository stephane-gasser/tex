#include "makeleftright.h"
#include "vardelimiter.h"
#include "police.h"

static int delimiter_factor(void) { return int_par(delimiter_factor_code); }
static int delimiter_shortfall(void) { return dimen_par(delimiter_shortfall_code); }

smallnumber makeleftright(halfword q, smallnumber style, scaled maxd, scaled maxh)
{
	if (style < 4)
		cursize = 0;
	else
		cursize = 16*((style-2)/2);
	scaled delta2 = maxd+axis_height(cursize);
	scaled delta1 = maxh+maxd-delta2;
	if (delta2 > delta1)
		delta1 = delta2;
	scaled delta = (delta1/500)*delimiter_factor();
	delta2 = 2*delta1-delimiter_shortfall();
	if (delta < delta2)
		delta = delta2;
	LeftRightNoad *Q;
	Q->num = q;
	new_hlist(q) = vardelimiter(Q->delimiter, cursize, delta)->num;
	return type(q)-(left_noad-open_noad);
}
