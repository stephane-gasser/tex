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
	curspan = link(p+1);
	link(align_head) = info(p+1);
	curalign = info(p);
	alignptr = link(p);
	freenode(p, 5);
}
