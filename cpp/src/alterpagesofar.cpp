#include "alterpagesofar.h"
#include "lecture.h"

void alterpagesofar(Token t)
{
	char c = t.chr;
	scanoptionalequals();
	pagesofar[c] = scan_normal_dimen();
}
