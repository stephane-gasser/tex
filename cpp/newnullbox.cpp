#include "newnullbox.h"
#include "getnode.h"

halfword newnullbox(void)
{
	halfword p = getnode(7);
	type(p) = hlist_node;
	subtype(p) = 0;
	mem[p+1].int_ = 0;
	mem[p+2].int_ = 0;
	mem[p+3].int_ = 0;
	mem[p+4].int_ = 0;
	link(p+5) = 0;
	type(p+5) = 0;
	subtype(p+5) = 0;
	mem[p+6].gr = 0.0;
	return p;
}
