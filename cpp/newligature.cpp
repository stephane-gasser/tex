#include "newligature.h"
#include "getnode.h"

halfword newligature(quarterword f, quarterword c, halfword q)
{
	auto p = getnode(2);
	type(p) = ligature_node;
	type(p+1) = f;
	subtype(p+1) = c;
	link(p+1) = q;
	subtype(p) = 0;
	return p;
}
