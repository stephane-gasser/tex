#include "newnullbox.h"
#include "getnode.h"

halfword newnullbox(void)
{
	halfword p = getnode(7);
	mem[p].hh.b0 = 0;
	mem[p].hh.b1 = 0;
	mem[p+1].int_ = 0;
	mem[p+2].int_ = 0;
	mem[p+3].int_ = 0;
	mem[p+4].int_ = 0;
	mem[p+5].hh.rh = 0;
	mem[p+5].hh.b0 = 0;
	mem[p+5].hh.b1 = 0;
	mem[p+6].gr = 0.0;
	return p;
}
