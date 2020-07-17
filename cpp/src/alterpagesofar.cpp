#include "alterpagesofar.h"
#include "lecture.h"

void alterpagesofar(halfword chr, halfword align)
{
	char c = chr;
	scanoptionalequals(align);
	pagesofar[c] = scan_normal_dimen(align);
}
