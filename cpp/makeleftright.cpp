#include "makeleftright.h"
#include "vardelimiter.h"

smallnumber makeleftright(halfword q, smallnumber style, scaled maxd, scaled  maxh)
{
	if (style < 4)
		cursize = 0;
	else
		cursize = 16*((style-2)/2);
	scaled delta2 = maxd+axis_height(cursize);
	scaled delta1 = maxh+maxd-delta2;
	if (delta2 > delta1)
		delta1 = delta2;
	scaled delta = (delta1/500)*int_par(delimiter_factor_code);
	delta2 = 2*delta1-dimen_par(delimiter_shortfall_code);
	if (delta < delta2)
		delta = delta2;
	width(q) = vardelimiter(delimiter(q), cursize, delta);
	return type(q)-10;
}
