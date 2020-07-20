#include "alterinteger.h"
#include "lecture.h"

void alterinteger(Token t)
{
	char c = t.chr;
	scanoptionalequals();
	(c == 0 ? deadcycles : insertpenalties) = scanint();
}
