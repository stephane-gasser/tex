#include "deletetokenref.h"
#include "flushlist.h"

void deletetokenref(halfword p)
{
	if (mem[p].hh.lh == 0)
		flushlist(p);
	else
		mem[p].hh.lh--;
}
