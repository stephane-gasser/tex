#include "popalignment.h"
#include "noeud.h"
#include "getavail.h"

void popalignment(void)
{
	free_avail(curhead);
	auto p = alignptr;
	curtail = link(p+4);
	curhead = info(p+4);
	alignstate = mem[p+3].int_;
	curloop = mem[p+2].int_;
	curspan = rlink(p);
	preamble() = llink(p);
	curalign = info(p);
	alignptr = link(p);
	freenode(p, align_stack_node_size);
}
