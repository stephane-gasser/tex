#include "finrow.h"
#include "hpack.h"
#include "popnest.h"
#include "appendtovlist.h"
#include "vpackage.h"
#include "alignpeek.h"
#include "begintokenlist.h"

void finrow(void)
{
	halfword p;
	if (curlist.modefield == -102)
	{
		p = hpack(link(curlist.headfield), 0, 1);
		popnest();
		appendtovlist(p);
		if (curhead != curtail)
		{
			link(curlist.tailfield) = link(curhead);
			curlist.tailfield = curtail;
		}
	}
	else
	{
		p = vpackage(link(curlist.headfield), 0, 1, 1073741823);
		popnest();
		link(curlist.tailfield) = p;
		curlist.tailfield = p;
		curlist.auxfield.hh.lh = 1000;
	}
	type(p) = 13;
	mem[p+6].int_ = 0;
	if (every_cr())
		begintokenlist(every_cr(), 13);
	alignpeek();
}

