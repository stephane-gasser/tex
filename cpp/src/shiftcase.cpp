#include "shiftcase.h"
#include "lecture.h"

void shiftcase(halfword b, halfword cs, halfword align)
{
	halfword p, t;
	eightbits c;
	p = scantoks(false, false, cs, align);
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
