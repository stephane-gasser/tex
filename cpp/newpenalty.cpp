#include "newpenalty.h"
#include "getnode.h"

halfword newpenalty(int m)
{
	auto p = getnode(2);
	mem[p].hh.b0 = 12;
	mem[p].hh.b1 = 0;
	mem[p+1].int_ = m;
	return p;
}
