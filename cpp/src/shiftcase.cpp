#include "shiftcase.h"
#include "lecture.h"

void shiftcase(Token tk)
{
	auto p = scantoks(false, false, tk);
	p = link(defref);
	while (p)
	{
		auto t = info(p);
		if (t < cs_token_flag+single_base)
		{
			eightbits c = t%(1<<8);
			if (equiv(tk.chr+c))
				info(p) = t-c+equiv(tk.chr+c);
		}
		p = link(p);
	}
	back_list(link(defref));
	link(defref) = avail;
	avail = defref;
}
