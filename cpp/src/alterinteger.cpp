#include "alterinteger.h"
#include "lecture.h"

void alterinteger(void)
{
	char c = curchr;
	scanoptionalequals();
	if (c == 0)
		deadcycles = scanint();
	else
		insertpenalties = scanint();
}
