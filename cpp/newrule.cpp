#include "newrule.h"
#include "getnode.h"

halfword newrule(void)
{
	auto p = getnode(4);
	type(p) = rule_node;
	subtype(p) = 0;
	mem[p+1].int_ = -0x40'00'00'00;
	mem[p+2].int_ = -0x40'00'00'00;
	mem[p+3].int_ = -0x40'00'00'00;
	return p;
}

