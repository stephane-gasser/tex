#include "flushlist.h"

void flushlist(halfword p)
{
	if (p)
	{
		halfword r = p, q;
		do
		{
			q = r;
			r = link(r);
		} while (r);
		link(q) = avail;
		avail = p;
	}
}
