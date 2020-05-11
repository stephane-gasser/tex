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
			if (type(tail) == ligature_node)
				p = tail+1;
			else
				return;
		internalfontnumber f = font(p);
		tail_append(newkern(char_italic(f, char_info(f, character(p)))));
		subtype(tail) = explicit_;
	}
}
