#include "freezepagespecs.h"

static int vsize(void) { return dimen_par(vsize_code); }

static void set_page_so_far_zero(int i)
{
	pagesofar[i] = 0;
}

void freezepagespecs(smallnumber s)
{
	pagecontents = s;
	page_goal = hsize();
	pagemaxdepth = vsize();
	for (int i = 1; i <= 7; i++)
		set_page_so_far_zero(i);
	leastpagecost = max_dimen;
}
