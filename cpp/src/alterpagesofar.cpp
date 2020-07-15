#include "alterpagesofar.h"
#include "lecture.h"

void alterpagesofar(halfword chr)
{
	char c = chr;
	scanoptionalequals();
	pagesofar[c] = scan_normal_dimen();
}
