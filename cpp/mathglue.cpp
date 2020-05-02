#include "mathglue.h"
#include "xovern.h"
#include "multandadd.h"
#include "xnoverd.h"
#include "getnode.h"

halfword mathglue(halfword g, scaled m)
{
	int n = xovern(m, 0x1'00'00);
	scaled f = remainder_;
	if (f < 0)
	{
		n--;
		f += 0x1'00'00;
	}
	auto p = getnode(4);
	mem[p+1].int_ = multandadd(n, mem[g+1].int_, xnoverd(mem[g+1].int_, f, 0x1'00'00), 0x3F'FF'FF'FF);
	type(p) = type(g);
	if (type(p) == 0)
		mem[p+2].int_ = multandadd(n, mem[g+2].int_, xnoverd(mem[g+2].int_, f, 0x1'00'00), 0x3F'FF'FF'FF);
	else
		mem[p+2].int_ = mem[g+2].int_;
	subtype(p) = subtype(g);
	if (subtype(p) == 0)
		mem[p+3].int_ = multandadd(n, mem[g+3].int_, xnoverd(mem[g+3].int_, f, 0x1'00'00), 0x3F'FF'FF'FF);
	else
		mem[p+3].int_ = mem[g+3].int_;
	return p;
}

