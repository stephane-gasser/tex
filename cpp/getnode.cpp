#include "getnode.h"
#include "overflow.h"

halfword getnode(int s)
{
	bool label20;
	halfword r;
	do
	{
		label20 = false;
		halfword p = rover;
		do
		{ 
			halfword q = p+info(p);
			while (link(q) == 0xFF'FF)
			{
				auto t = link(q+1);
				if (q == rover)
					rover = t;
				info(t+1) = info(q+1);
				link(info(q+1)+1) = t;
				q += info(q);
			}
			r = q-s;
			if (r > p+1)
			{
				info(p) = r-p;
				rover = p;
				link(r) = 0;
				return r;
			}
			if (r == p)
			if (link(p+1) != p)
			{
				rover = link(p+1);
				int t = info(p+1);
				info(rover+1) = t;
				link(t+1) = rover;
				link(r) = 0;
				return r;
			}
			info(p) = q-p;
			p = link(p+1);
		} while (p != rover);
		if (s == 0x40'00'00'00)
			return 0xFF'FF;
		if (lomemmax+2 < himemmin && lomemmax+2 <= 0xFF'FF)
		{
			int t;
			if (himemmin-lomemmax >= 1998)
				t = lomemmax+1000;
			else
				t = lomemmax+1+(himemmin-lomemmax)/2;
			p = info(rover+1);
			halfword q = lomemmax;
			link(p+1) = q;
			info(rover+1) = q;
			if (t > 0xFF'FF)
				t = 0xFF'FF;
			link(q+1) = rover;
			info(q+1) = p;
			link(q) = 0xFF'FF;
			info(q) = t-lomemmax;
			lomemmax = t;
			link(lomemmax) = 0;
			info(lomemmax) = 0;
			rover = q;
			label20 = true;
		}
	} while (label20);
	overflow(300, memmax+1-memmin); //main memory size
	link(r) = 0;
	return r;
}
