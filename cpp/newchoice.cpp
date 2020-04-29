#include "newchoice.h"
#include "getnode.h"

halfword newchoice(void)
{
	auto p = getnode(3);
	type(p) = choice_node;
	subtype(p) = 0;
	info(p+1) = 0;
	link(p+1) = 0;
	info(p+2) = 0;
	link(p+2) = 0;
	return p;
}
