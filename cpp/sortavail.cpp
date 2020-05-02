#include "sortavail.h"
#include "getnode.h"

void sortavail(void)
{
	halfword p = getnode(0x40'00'00'00);
	p = link(rover+1);
	link(rover+1) = 0xFF'FF;
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
	while (link(p+1) != 0xFF'FF)
	{
		info(link(p+1)+1) = p;
		p = link(p+1);
	}
	link(p+1) = rover;
	info(rover+1) = p;
}
