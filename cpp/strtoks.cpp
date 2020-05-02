#include "strtoks.h"
#include "getavail.h"
#include "overflow.h"

halfword strtoks(poolpointer b)
{
	if (poolptr + 1 > poolsize)
		overflow(257, poolsize - initpoolptr); //pool size
	halfword p = temp_head;
	link(p) = 0;
	for (auto k = b; k < poolptr; k++)
	{
		halfword t = strpool[k];
		if (t == ' ')
			t = 0x0A'00+' ';
		else
			t += 0x0C'00;
		auto q = avail;
		if (q == 0)
			q = getavail();
		else
		{
			avail = link(q);
			link(q) = 0;
		}
		link(p) = q;
		info(q) = t;
		p = q;
	}
	poolptr = b;
	return p;
}

