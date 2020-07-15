#include "finrow.h"
#include "hpack.h"
#include "popnest.h"
#include "noeud.h"
#include "vpackage.h"
#include "alignpeek.h"
#include "lecture.h"

void finrow(void)
{
	halfword p;
	if (mode == -hmode)
	{
		p = hpack(link(head), 0, additional);
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
		p = vpack(link(head), 0, additional);
		popnest();
		link(tail) = p;
		tail = p;
		space_factor = 1000;
	}
	type(p) = unset_node;
	glue_stretch(p) = 0;
	if (every_cr())
		begintokenlist(every_cr(), every_cr_text);
	alignpeek();
}

