#include "indentinhmode.h"
#include "newnullbox.h"
#include "newnoad.h"

void indentinhmode(void)
{
	if (curchr > 0)
	{
		auto p = newnullbox();
		mem[p+1].int_ = eqtb[5830].int_;
		if (abs(curlist.modefield) == 102)
			curlist.auxfield.hh.lh = 1000;
		else
		{
			auto q = newnoad();
			link(q+1) = 2;
			info(q+1) = p;
			p = q;
		}
		link(curlist.tailfield) = p;
		curlist.tailfield = link(curlist.tailfield);
	}
}
