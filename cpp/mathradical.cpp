#include "mathradical.h"
#include "scandelimiter.h"
#include "scanmath.h"
#include "getnode.h"

void mathradical(void)
{
	tail_append(getnode(5));
	type(tail) = 24;
	subtype(tail) = 0;
	mem[tail+1].hh = emptyfield;
	mem[tail+3].hh = emptyfield;
	mem[tail+2].hh = emptyfield;
	scandelimiter(tail+4, true);
	scanmath(tail+1);
}
