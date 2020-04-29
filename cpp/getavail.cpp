#include "getavail.h"
#include "runaway.h"
#include "overflow.h"

halfword getavail(void)
{
	halfword p = avail;
	if (p)
		avail = link(avail);
	else 
		if (memend < memmax)
			p = ++memend;
		else
		{
			p = --himemmin;
			if (himemmin <= lomemmax)
			{
				runaway();
				overflow(300, memmax+1-memmin); //main memory size
			}
		}
	link(p) = 0;
	return p;
}
