#include "newmath.h"
#include "getnode.h"

halfword newmath(scaled w, smallnumber s)
{ 
	auto p = getnode(2);
	type(p) = math_node;
	subtype(p) = s;
	width(p) = w;
	return p;
}

