#include "mathglue.h"
#include "xovern.h"
#include "multandadd.h"
#include "xnoverd.h"
#include "getnode.h"

halfword mathglue(halfword g, scaled m)
{
	int n = xovern(m, 65536);
	scaled f = remainder_;
	if (f < 0)
	{
		n--;
		f += 65536;
	}
	auto p = getnode(4);
	mem[p+1].int_ = multandadd(n, mem[g+1].int_, xnoverd(mem[g+1].int_, f, 65536), 1073741823);
	type(p) = type(g);
	if (type(p) == 0)
		mem[p+2].int_ = multandadd(n, mem[g+2].int_, xnoverd(mem[g+2].int_, f, 65536), 1073741823);
	else
		mem[p+2].int_ = mem[g+2].int_;
	subtype(p) = subtype(g);
	if (subtype(p) == 0)
		mem[p+3].int_ = multandadd(n, mem[g+3].int_, xnoverd(mem[g+3].int_, f, 65536), 1073741823);
	else
		mem[p+3].int_ = mem[g+3].int_;
	return p;
}

