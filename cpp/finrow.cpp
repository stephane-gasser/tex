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
	if (mode == -hmode)
	{
		p = hpack(link(head), 0, 1);
		popnest();
		appendtovlist(p);
		if (curhead != curtail)
		{
			link(tail) = link(curhead);
			tail = curtail;
		}
	}
	else
	{
		p = vpackage(link(head), 0, 1, 0x3F'FF'FF'FF);
		popnest();
		link(tail) = p;
		tail = p;
		space_factor = 1000;
	}
	type(p) = 13;
	mem[p+6].int_ = 0;
	if (every_cr())
		begintokenlist(every_cr(), 13);
	alignpeek();
}

