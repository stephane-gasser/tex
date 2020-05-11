#include "newrule.h"
#include "getnode.h"

halfword newrule(void)
{
	auto p = getnode(4);
	type(p) = rule_node;
	subtype(p) = 0;
	width(p) = null_flag;
	depth(p) = null_flag;
	height(p) = null_flag;
	return p;
}

