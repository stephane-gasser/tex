#include "appendkern.h"
#include "scandimen.h"
#include "newkern.h"

void appendkern(void)
{
	auto s = curchr;
	scandimen(s == 99, false, false);
	link(curlist.tailfield) = newkern(curval);
	curlist.tailfield = link(curlist.tailfield);
	subtype(curlist.tailfield) = s;
}
