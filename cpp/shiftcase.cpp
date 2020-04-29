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
			if (eqtb[b+c].hh.rh)
				info(p) = t-c+eqtb[b+c].hh.rh;
		}
		p = link(p);
	}
	begintokenlist(link(defref), 3);
	link(defref) = avail;
	avail = defref;
}
