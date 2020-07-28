#include "sortavail.h"
#include "noeud.h"

//! sorts the available variable-size nodes by location
void sortavail(void)
{
	auto p = getnode(1<<30);
	p = rlink(rover);
	rlink(rover) = empty_flag;
	halfword oldrover = rover;
	while (p != oldrover)
		if (p < rover)
		{
			auto q = p;
			p = rlink(q);
			rlink(q) = rover;
			rover = q;
		}
		else
		{
			halfword q = rover;
			while (rlink(q) < p)
				q = rlink(q);
			auto r = rlink(p);
			rlink(p) = rlink(q);
			rlink(q) = p;
			p = r;
		}
	p = rover;
	while (rlink(p) != empty_flag)
	{
		llink(rlink(p)) = p;
		p = rlink(p);
	}
	rlink(p) = rover;
	llink(rover) = p;
}
