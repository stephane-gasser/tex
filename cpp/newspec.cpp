#include "newspec.h"
#include "getnode.h"

halfword newspec(halfword p)
{
	auto q = getnode(4);
	mem[q] = mem[p];
	link(q) = 0;
	mem[q+1].int_ = mem[p+1].int_;
	mem[q+2].int_ = mem[p+2].int_;
	mem[q+3].int_ = mem[p+3].int_;
	return q;
}
