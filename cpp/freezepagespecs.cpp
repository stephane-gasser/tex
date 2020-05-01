#include "freezepagespecs.h"

void freezepagespecs(smallnumber s)
{
	pagecontents = s;
	pagesofar[0] = dimen_par(hsize_code);
	pagemaxdepth = dimen_par(vsize_code);
	for (int i = 1; i <= 7; i++)
		pagesofar[i] = 0;
	leastpagecost = 1073741823;
}
