#include "sortavail.h"
#include "erreur.h"

static halfword getnode(void)
{
	int s = 1<<30;
	halfword p = rover;
	do
	{ 
		halfword q = p+node_size(p);
		while (link(q) == empty_flag)
		{
			auto t = rlink(q);
			if (q == rover)
				rover = t;
			llink(t) = llink(q);
			rlink(llink(q)) = t;
			q += node_size(q);
		}
		halfword r = q-s;
		if (r > p+1)
		{
			node_size(p) = r-p;
			rover = p;
			link(r) = 0;
			return r;
		}
		if (r == p)
		if (rlink(p) != p)
		{
			rover = rlink(p);
			int t = llink(p);
			llink(rover) = t;
			rlink(t) = rover;
			link(r) = 0;
			return r;
		}
		node_size(p) = q-p;
		p = rlink(p);
	} while (p != rover);
	return empty_flag;
}

//! sorts the available variable-size nodes by location
void sortavail(void)
{
	auto p = getnode();
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
