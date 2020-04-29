#include "freezepagespecs.h"

void freezepagespecs(smallnumber s)
{
	pagecontents = s;
	pagesofar[0] = eqtb[5834].int_;
	pagemaxdepth = eqtb[5835].int_;
	for (int i = 1; i <= 7; i++)
		pagesofar[i] = 0;
	leastpagecost = 1073741823;
}
