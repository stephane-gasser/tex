#include "mathkern.h"
#include "xovern.h"
#include "xnoverd.h"
#include "multandadd.h"

void mathkern(halfword p, scaled m)
{
	if (subtype(p) == 99)
	{
		int n = xovern(m, 0x1'00'00);
		scaled f = remainder_;
		if (f < 0)
		{
			n--;
			f += 0x1'00'00;
		}
		mem[p+1].int_ = multandadd(n, mem[p+1].int_, xnoverd(mem[p+1].int_, f, 0x1'00'00), max_dimen);
		subtype(p) = 1;
	}
}
