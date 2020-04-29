#include "newnoad.h"
#include "getnode.h"

halfword newnoad(void)
{
	auto p = getnode(4);
	type(p) = 16;
	subtype(p) = 0;
	mem[p+1].hh = emptyfield;
	mem[p+3].hh = emptyfield;
	mem[p+2].hh = emptyfield;
	return p;
}
