#include "newkern.h"
#include "getnode.h"

halfword newkern(scaled w)
{
	auto p = getnode(2);
	type(p) = kern_node;
	subtype(p) = 0;
	mem[p+1].int_ = w;
	return p;
}
