#include "badness.h"

halfword badness(scaled t, scaled s)
{
	if (t == 0)
		return 0;
	if (s <= 0)
		return 10000;
	int r = (t <= 7230584) ? (t*297)/s : (s >= 1663497) ? t/(s/297) : t;
	if (r > 1290)
		return 10000;
	return (r*r*r+131072)/262144;
}
