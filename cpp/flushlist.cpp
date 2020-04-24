#include "flushlist.h"

void flushlist(halfword p)
{
	if (p)
	{
		halfword r = p, q;
		do
		{
			q = r;
			r = mem[r].hh.rh;
		} while (r);
		mem[q].hh.rh = avail;
		avail = p;
	}
}
