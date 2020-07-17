#include "alterinteger.h"
#include "lecture.h"

void alterinteger(halfword chr, halfword align)
{
	char c = chr;
	scanoptionalequals(align);
	if (c == 0)
		deadcycles = scanint(align);
	else
		insertpenalties = scanint(align);
}
