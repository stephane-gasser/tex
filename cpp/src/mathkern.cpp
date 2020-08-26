#include "mathkern.h"
#include "xovern.h"
#include "xnoverd.h"
#include "multandadd.h"

void mathkern(KernNode *p, scaled m)
{
	if (p->subtype == mu_glue)
	{
		int n = xovern(m, unity);
		scaled f = remainder_;
		if (f < 0)
		{
			n--;
			f += unity;
		}
		p->width = mu_mult(n, p->width);
		p->subtype = 1;
	}
}
