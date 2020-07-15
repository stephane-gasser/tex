#include "sortavail.h"
#include "noeud.h"

void sortavail(void)
{
	halfword p = getnode(1<<30);
	p = link(rover+1);
	link(rover+1) = empty_flag;
	halfword oldrover = rover;
	while (p != oldrover)
		if (p < rover)
		{
			halfword q = p;
			p = link(q+1);
			link(q+1) = rover;
			rover = q;
		}
		else
		{
			halfword q = rover;
			while (link(q+1) < p)
				q = link(q+1);
			halfword r = link(p+1);
			link(p+1) = link(q+1);
			link(q+1) = p;
			p = r;
		}
	p = rover;
	while (link(p+1) != empty_flag)
	{
		info(link(p+1)+1) = p;
		p = link(p+1);
	}
	link(p+1) = rover;
	info(rover+1) = p;
}
