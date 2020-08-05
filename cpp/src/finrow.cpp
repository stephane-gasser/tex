#include "finrow.h"
#include "popnest.h"
#include "noeud.h"
#include "boite.h"
#include "alignpeek.h"
#include "lecture.h"

void finrow(halfword &loop)
{
	LinkedNode *p;
	if (mode == -hmode)
	{
		p = hpack(head->link, 0, additional);
		popnest();
		appendtovlist(p->num);
		if (curhead != curtail)
		{
			tail->link = curhead->link;
			tail = curtail;
		}
	}
	else
	{
		p = vpack(head->link, 0, additional);
		popnest();
		tail->link = p;
		tail = p;
		space_factor = 1000;
	}
	p->type = unset_node;
	glue_stretch(p->num) = 0;
	if (every_cr())
		begintokenlist(every_cr(), every_cr_text);
	alignpeek(loop);
}

