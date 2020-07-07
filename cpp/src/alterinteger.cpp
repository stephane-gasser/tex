#include "alterinteger.h"
#include "lecture.h"

void alterinteger(void)
{
	char c = curchr;
	scanoptionalequals();
	curval = scanint();
	if (c == 0)
		deadcycles = curval;
	else
		insertpenalties = curval;
}
