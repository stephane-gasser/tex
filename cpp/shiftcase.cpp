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
		if (t < cs_token_flag+single_base)
		{
			c = t%0x1'00;
			if (equiv(b+c))
				info(p) = t-c+equiv(b+c);
		}
		p = link(p);
	}
	back_list(link(defref));
	link(defref) = avail;
	avail = defref;
}
