#include "newstyle.h"
#include "getnode.h"

halfword newstyle(smallnumber s)
{
	auto p = getnode(3);
	type(p) = style_node;
	subtype(p) = s;
	mem[p+1].int_ = 0;
	mem[p+2].int_ = 0;
	return p;
}
