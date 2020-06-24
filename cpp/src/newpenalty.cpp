#include "newpenalty.h"
#include "getnode.h"

halfword newpenalty(int m)
{
	auto p = getnode(2);
	type(p) = penalty_node;
	subtype(p) = 0;
	penalty(p) = m;
	return p;
}
