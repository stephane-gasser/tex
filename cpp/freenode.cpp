#include "freenode.h"

void freenode(halfword p, halfword s)
{
	mem[p].hh.lh = s;
	mem[p].hh.rh = 65535;
	halfword q = mem[rover+1].hh.lh;
	mem[p+1].hh.lh = q;
	mem[p+1].hh.rh = rover;
	mem[rover+1].hh.lh = p;
	mem[q+1].hh.rh = p;
}
