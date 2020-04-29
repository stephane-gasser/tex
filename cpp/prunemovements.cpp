#include "prunemovements.h"
#include "freenode.h"

void prunemovements(int l)
{
	while (downptr)
	{
		if (mem[downptr+2].int_ < l)
			break;
		auto p = downptr;
		downptr = link(p);
		freenode(p, 3);
	}
	while (rightptr)
	{
		if (mem[rightptr+2].int_ < l)
			break;
		auto p = rightptr;
		rightptr = link(p);
		freenode(p, 3);
	}
}

