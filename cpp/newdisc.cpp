#include "newdisc.h"
#include "getnode.h"

halfword newdisc(void)
{
	auto p = getnode(2);
	mem[p].hh.b0 = 7;
	mem[p].hh.b1 = 0;
	mem[p+1].hh.lh = 0;
	mem[p+1].hh.rh = 0;
	return p;
}
