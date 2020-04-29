#include "appenditaliccorrection.h"
#include "newkern.h"

void appenditaliccorrection(void)
{
	if (curlist.tailfield != curlist.headfield)
	{
		halfword p;
		if (curlist.tailfield >= himemmin)
			p = curlist.tailfield;
		else 
			if (type(curlist.tailfield) == ligature_node) //6
				p = curlist.tailfield+1;
			else
				return;
		internalfontnumber f = type(p);
		link(curlist.tailfield) = newkern(fontinfo[italicbase[f]+(fontinfo[charbase[f]+subtype(p)].qqqq.b2)/4].int_);
		curlist.tailfield = link(curlist.tailfield);
		subtype(curlist.tailfield) = 1;
	}
}
