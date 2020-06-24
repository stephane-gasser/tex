#include "newdisc.h"
#include "getnode.h"

halfword newdisc(void)
{
	auto p = getnode(2);
	type(p) = disc_node;
	replace_count(p) = 0;
	pre_break(p) = 0;
	post_break(p) = 0;
	return p;
}
