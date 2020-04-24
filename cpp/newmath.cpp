#include "newmath.h"
#include "getnode.h"

halfword newmath(scaled w, smallnumber s)
{ 
	auto p = getnode(2);
	mem[p].hh.b0 = 9;
	mem[p].hh.b1 = s;
	mem[p+1].int_ = w;
	return p;
}

