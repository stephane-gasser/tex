#include "sortavail.h"
#include "getnode.h"

void sortavail(void)
{
	halfword p = getnode(1073741824);
	p = mem[rover+1].hh.rh;
	mem[rover+1].hh.rh = 65535;
	halfword oldrover = rover;
	while (p != oldrover)
		if (p < rover)
		{
			halfword q = p;
			p = mem[q+1].hh.rh;
			mem[q+1].hh.rh = rover;
			rover = q;
		}
		else
		{
			halfword q = rover;
			while (mem[q+1].hh.rh < p)
			q = mem[q+1].hh.rh;
			halfword r = mem[p+1].hh.rh;
			mem[p+1].hh.rh = mem[q+1].hh.rh;
			mem[q+1].hh.rh = p;
			p = r;
		}
	p = rover;
	while (mem[p+1].hh.rh != 65535)
	{
		mem[mem[p+1].hh.rh+1].hh.lh = p;
		p = mem[p+1].hh.rh;
	}
	mem[p+1].hh.rh = rover;
	mem[rover+1].hh.lh = p;
}
