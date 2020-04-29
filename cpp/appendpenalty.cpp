#include "appendpenalty.h"
#include "scanint.h"
#include "buildpage.h"
#include "newpenalty.h"

void appendpenalty(void)
{
	scanint();
	link(curlist.tailfield) = newpenalty(curval);
	curlist.tailfield = link(curlist.tailfield);
	if (curlist.modefield == 1)
		buildpage();
}
