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
			halfword q = p+mem[p].hh.lh;
			while (mem[q].hh.rh == 65535)
			{
				int t = mem[q+1].hh.rh;
				if (q == rover)
					rover = t;
				mem[t+1].hh.lh = mem[q+1].hh.lh;
				mem[mem[q+1].hh.lh+1].hh.rh = t;
				q += mem[q].hh.lh;
			}
			r = q-s;
			if (r > p+1)
			{
				mem[p].hh.lh = r - p;
				rover = p;
				mem[r].hh.rh = 0;
				return r;
			}
			if (r == p)
			if (mem[p+1].hh.rh != p)
			{
				rover = mem[p+1].hh.rh;
				int t = mem[p+1].hh.lh;
				mem[rover+1].hh.lh = t;
				mem[t+1].hh.rh = rover;
				mem[r].hh.rh = 0;
				return r;
			}
			mem[p].hh.lh = q-p;
			p = mem[p+1].hh.rh;
		} while (p != rover);
		if (s == 1073741824)
			return 65535;
		if (lomemmax+2 < himemmin && lomemmax+2 <= 65535)
		{
			int t;
			if (himemmin-lomemmax >= 1998)
				t = lomemmax+1000;
			else
				t = lomemmax+1+(himemmin-lomemmax)/2;
			p = mem[rover+1].hh.lh;
			halfword q = lomemmax;
			mem[p+1].hh.rh = q;
			mem[rover+1].hh.lh = q;
			if (t > 65535)
				t = 65535;
			mem[q+1].hh.rh = rover;
			mem[q+1].hh.lh = p;
			mem[q].hh.rh = 65535;
			mem[q].hh.lh = t-lomemmax;
			lomemmax = t;
			mem[lomemmax].hh.rh = 0;
			mem[lomemmax].hh.lh = 0;
			rover = q;
			label20 = true;
		}
	} while (label20);
	overflow(300, memmax+1-memmin); //main memory size
	mem[r].hh.rh = 0;
	return r;
}
