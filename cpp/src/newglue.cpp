#include "newglue.h"
#include "getnode.h"

halfword newglue(halfword q)
{
	auto p = getnode(2);
	type(p) = glue_node;
	subtype(p) = 0;
	link(p+1) = 0;
	info(p+1) = q;
	link(q)++;
	return p;
}
