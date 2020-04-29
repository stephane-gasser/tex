#include "mathradical.h"
#include "scandelimiter.h"
#include "scanmath.h"
#include "getnode.h"

void mathradical(void)
{
	link(curlist.tailfield) = getnode(5);
	curlist.tailfield = link(curlist.tailfield);
	type(curlist.tailfield) = 24;
	subtype(curlist.tailfield) = 0;
	mem[curlist.tailfield+1].hh = emptyfield;
	mem[curlist.tailfield+3].hh = emptyfield;
	mem[curlist.tailfield+2].hh = emptyfield;
	scandelimiter(curlist.tailfield+4, true);
	scanmath(curlist.tailfield+1);
}
