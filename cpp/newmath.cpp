#include "newmath.h"
#include "getnode.h"

halfword newmath(scaled w, smallnumber s)
{ 
	auto p = getnode(2);
	type(p) = math_node;
	subtype(p) = s;
	mem[p+1].int_ = w;
	return p;
}

