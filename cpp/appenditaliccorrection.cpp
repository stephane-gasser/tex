#include "appenditaliccorrection.h"
#include "newkern.h"

void appenditaliccorrection(void)
{
	if (tail != head)
	{
		halfword p;
		if (tail >= himemmin)
			p = tail;
		else 
			if (type(tail) == ligature_node) //6
				p = tail+1;
			else
				return;
		internalfontnumber f = type(p);
		tail_append(newkern(fontinfo[italicbase[f]+(fontinfo[charbase[f]+subtype(p)].qqqq.b2)/4].int_));
		subtype(tail) = 1;
	}
}
