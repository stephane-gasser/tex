#include "appenditaliccorrection.h"
#include "newkern.h"

void appenditaliccorrection(void)
{
	if (tail != head)
	{
		halfword p;
		if (is_char_node(tail))
			p = tail;
		else 
			if (type(tail) == ligature_node)
				p = lig_char(tail);
			else
				return;
		auto f = font(p);
		tail_append(newkern(char_italic(f, char_info(f, character(p)))));
		subtype(tail) = explicit_;
	}
}
