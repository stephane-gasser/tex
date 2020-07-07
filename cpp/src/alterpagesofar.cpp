#include "alterpagesofar.h"
#include "lecture.h"

void alterpagesofar(void)
{
	char c = curchr;
	scanoptionalequals();
	curval = scan_normal_dimen();
	pagesofar[c] = curval;
}
