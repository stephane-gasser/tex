#include "alterinteger.h"
#include "scanoptionalequals.h"
#include "scanint.h"

void alterinteger(void)
{
	char c = curchr;
	scanoptionalequals();
	scanint();
	if (c == 0)
		deadcycles = curval;
	else
		insertpenalties = curval;
}
