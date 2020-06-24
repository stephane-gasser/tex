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
		width(p) = mu_mult(n, width(p));
		subtype(p) = 1;
	}
}
