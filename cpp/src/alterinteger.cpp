#include "alterinteger.h"
#include "lecture.h"

void alterinteger(halfword chr)
{
	char c = chr;
	scanoptionalequals();
	if (c == 0)
		deadcycles = scanint();
	else
		insertpenalties = scanint();
}
