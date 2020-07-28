#include "pushalignment.h"
#include "noeud.h"

void pushalignment(halfword loop)
{
	auto p = getnode(align_stack_node_size);
	link(p) = alignptr;
	info(p) = curalign;
	llink(p) = preamble();
	rlink(p) = curspan;
	mem[p+2].int_ = loop;
	mem[p+3].int_ = alignstate;
	info(p+4) = curhead;
	link(p+4) = curtail;
	alignptr = p;
	curhead = getavail();
}
