#include "shiftcase.h"
#include "scantoks.h"
#include "begintokenlist.h"

void shiftcase(void)
{
	halfword b, p, t;
	eightbits c;
	b = curchr;
	p = scantoks(false, false);
	p = link(defref);
	while (p)
	{
		t = info(p);
		if (t < 4352)
		{
			c = t%256;
			if (equiv(b+c))
				info(p) = t-c+equiv(b+c);
		}
		p = link(p);
	}
	begintokenlist(link(defref), 3);
	link(defref) = avail;
	avail = defref;
}
