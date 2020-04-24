#include "newkern.h"
#include "getnode.h"

halfword newkern(scaled w)
{
	auto p = getnode(2);
	mem[p].hh.b0 = 11;
	mem[p].hh.b1 = 0;
	mem[p+1].int_ = w;
	return p;
}
