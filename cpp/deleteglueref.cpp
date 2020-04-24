#include "deleteglueref.h"
#include "freenode.h"

void deleteglueref(halfword p)
{
	if (mem[p].hh.rh == 0)
		freenode(p, 4);
	else
		mem[p].hh.rh--;
}
