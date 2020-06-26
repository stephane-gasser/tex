#include "badness.h"

//! Compute badness, given <em> t >= 0 </em>
halfword badness(scaled t, scaled s)
{
	if (t == 0)
		return 0;
	if (s <= 0)
		return inf_bad;
	// approximation to \f$\alpha t/s\f$, where \f$\alpha^3\approx100\cdot2^{18}\f$
	int r = (t <= 7230584) ? (t*297)/s : (s >= 1663497) ? t/(s/297) : t; //$297^3=99.94\times2^{18}$
	if (r > 1290)
		return inf_bad;
	return (r*r*r+1<<17)>>18; //that was \f$r^3/2^{18}\f$, rounded to the nearest integer
}
