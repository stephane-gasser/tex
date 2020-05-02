#include "freenode.h"

void freenode(halfword p, halfword s)
{
	info(p) = s;
	link(p) = 0xFF'FF;
	halfword q = info(rover+1);
	info(p+1) = q;
	link(p+1) = rover;
	info(rover+1) = p;
	link(q+1) = p;
}
