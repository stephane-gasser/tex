#include "newligitem.h"
#include "getnode.h"

halfword newligitem(quarterword c)
{
	auto p = getnode(2);
	mem[p].hh.b1 = c;
	mem[p+1].hh.rh = 0;
	return p;
}
