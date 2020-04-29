#include "alterpagesofar.h"
#include "scanoptionalequals.h"
#include "scandimen.h"

void alterpagesofar(void)
{
	char c = curchr;
	scanoptionalequals();
	scandimen(false, false, false);
	pagesofar[c] = curval;
}
