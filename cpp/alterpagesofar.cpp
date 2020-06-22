#include "alterpagesofar.h"
#include "scanoptionalequals.h"
#include "scandimen.h"

void alterpagesofar(void)
{
	char c = curchr;
	scanoptionalequals();
	scan_normal_dimen();
	pagesofar[c] = curval;
}
