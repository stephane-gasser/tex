#include "newligature.h"
#include "getnode.h"

halfword newligature(quarterword f, quarterword c, halfword q)
{
	auto p = getnode(2);
	mem[p].hh.b0 = 6;
	mem[p+1].hh.b0 = f;
	mem[p+1].hh.b1 = c;
	mem[p+1].hh.rh = q;
	mem[p].hh.b1 = 0;
	return p;
}
