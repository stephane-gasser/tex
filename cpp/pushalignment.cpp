#include "pushalignment.h"
#include "getavail.h"
#include "getnode.h"

void pushalignment(void)
{
	auto p = getnode(5);
	link(p) = alignptr;
	info(p) = curalign;
	info(p+1) = link(align_head);
	link(p+1) = curspan;
	mem[p+2].int_ = curloop;
	mem[p+3].int_ = alignstate;
	info(p+4) = curhead;
	link(p+4) = curtail;
	alignptr = p;
	curhead = getavail();
}
