#include "mathkern.h"
#include "xovern.h"
#include "xnoverd.h"
#include "multandadd.h"

void mathkern(halfword p, scaled m)
{
	if (subtype(p) == 99)
	{
		int n = xovern(m, 65536);
		scaled f = remainder_;
		if (f < 0)
		{
			n--;
			f += 65536;
		}
		mem[p+1].int_ = multandadd(n, mem[p+1].int_, xnoverd(mem[p+1].int_, f, 65536), 1073741823);
		subtype(p) = 1;
	}
}
