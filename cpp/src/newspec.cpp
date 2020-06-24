#include "newspec.h"
#include "getnode.h"

halfword newspec(halfword p)
{
	auto q = getnode(4);
	mem[q] = mem[p];
	link(q) = 0;
	mem[q+1] = mem[p+1];
	mem[q+2] = mem[p+2];
	mem[q+3] = mem[p+3];
	return q;
}
