#include "newdisc.h"
#include "getnode.h"

halfword newdisc(void)
{
	auto p = getnode(2);
	type(p) = disc_node;
	subtype(p) = 0;
	info(p+1) = 0;
	link(p+1) = 0;
	return p;
}
