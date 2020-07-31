#include "popalignment.h"
#include "noeud.h"

void popalignment(halfword &loop)
{
	delete curhead; 
	auto p = alignptr;
	curtail->num = link(p+4);
	curhead->num = info(p+4);
	alignstate = mem[p+3].int_;
	loop = mem[p+2].int_;
	curspan = rlink(p);
	preamble() = llink(p);
	curalign = info(p);
	alignptr = link(p);
	freenode(p, align_stack_node_size);
}
