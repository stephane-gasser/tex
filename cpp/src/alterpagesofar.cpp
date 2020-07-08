#include "alterpagesofar.h"
#include "lecture.h"

void alterpagesofar(void)
{
	char c = curchr;
	scanoptionalequals();
	pagesofar[c] = scan_normal_dimen();
}
