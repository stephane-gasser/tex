#include "newligitem.h"
#include "getnode.h"

halfword newligitem(quarterword c)
{
	auto p = getnode(2);
	subtype(p) = c;
	link(p+1) = 0;
	return p;
}
