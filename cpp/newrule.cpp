#include "newrule.h"
#include "getnode.h"

halfword newrule(void)
{
	auto p = getnode(4);
	type(p) = rule_node;
	subtype(p) = 0;
	mem[p+1].int_ = -1073741824;
	mem[p+2].int_ = -1073741824;
	mem[p+3].int_ = -1073741824;
	return p;
}

