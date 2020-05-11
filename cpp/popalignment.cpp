#include "popalignment.h"
#include "freenode.h"

void popalignment(void)
{
	link(curhead) = avail;
	avail = curhead;
	auto p = alignptr;
	curtail = link(p+4);
	curhead = info(p+4);
	alignstate = mem[p+3].int_;
	curloop = mem[p+2].int_;
	curspan = rlink(p);
	preamble() = llink(p);
	curalign = info(p);
	alignptr = link(p);
	freenode(p, 5);
}
