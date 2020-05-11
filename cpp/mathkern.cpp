#include "mathkern.h"
#include "xovern.h"
#include "xnoverd.h"
#include "multandadd.h"

void mathkern(halfword p, scaled m)
{
	if (subtype(p) == mu_glue)
	{
		int n = xovern(m, unity);
		scaled f = remainder_;
		if (f < 0)
		{
			n--;
			f += unity;
		}
		width(p) = multandadd(n, width(p), xnoverd(width(p), f, unity), max_dimen);
		subtype(p) = 1;
	}
}
