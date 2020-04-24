#include "getavail.h"
#include "runaway.h"
#include "overflow.h"

halfword getavail(void)
{
	halfword p = avail;
	if (p)
		avail = mem[avail].hh.rh;
	else 
		if (memend < memmax)
			p = ++memend;
		else
		{
			p = --himemmin;
			if (himemmin <= lomemmax)
			{
				runaway();
				overflow(300, memmax + 1 - memmin); //main memory size
			}
		}
	mem[p].hh.rh = 0;
	return p;
}
