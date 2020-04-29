#include "initspan.h"
#include "pushnest.h"
#include "normalparagraph.h"

void initspan(halfword p)
{
	pushnest();
	if (curlist.modefield == -102)
		curlist.auxfield.hh.lh = 1000;
	else
	{
		curlist.auxfield.int_ = -65536000;
		normalparagraph();
	}
	curspan = p;
}
