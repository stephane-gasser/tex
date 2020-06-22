#include "newnoad.h"
#include "getnode.h"

halfword newnoad(void)
{
	auto p = getnode(noad_size);
	type(p) = ord_noad;
	subtype(p) = normal;
	mem[p+1].hh = emptyfield;
	mem[p+3].hh = emptyfield;
	mem[p+2].hh = emptyfield;
	return p;
}
