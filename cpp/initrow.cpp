#include "initrow.h"
#include "pushnest.h"
#include "initspan.h"
#include "newglue.h"

void initrow(void)
{
	pushnest();
	curlist.modefield = -103-curlist.modefield;
	if (curlist.modefield == -102)
		curlist.auxfield.hh.lh = 0;
	else
		curlist.auxfield.int_ = 0;
	{
		link(curlist.tailfield) = newglue(info(link(align_head)+1));
		curlist.tailfield = link(curlist.tailfield);
	}
	subtype(curlist.tailfield) = 12;
	curalign = link(link(align_head));
	curtail = curhead;
	initspan(curalign);
}
