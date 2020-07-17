#include "popalignment.h"
#include "noeud.h"
#include "getavail.h"

void popalignment(halfword &loop, halfword &span, halfword &align)
{
	free_avail(curhead);
	auto p = alignptr;
	curtail = link(p+4);
	curhead = info(p+4);
	alignstate = mem[p+3].int_;
	loop = mem[p+2].int_;
	span = rlink(p);
	preamble() = llink(p);
	align = info(p);
	alignptr = link(p);
	freenode(p, align_stack_node_size);
}
