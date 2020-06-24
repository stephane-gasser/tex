#include "mathradical.h"
#include "scandelimiter.h"
#include "scanmath.h"
#include "getnode.h"

void mathradical(void)
{
	tail_append(getnode(radical_noad_size));
	type(tail) = radical_noad;
	subtype(tail) = normal;
	mem[nucleus(tail)].hh = emptyfield;
	mem[subscr(tail)].hh = emptyfield;
	mem[supscr(tail)].hh = emptyfield;
	scandelimiter(left_delimiter(tail), true);
	scanmath(nucleus(tail));
}
