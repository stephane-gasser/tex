#include "popnest.h"

void popnest(void)
{
	mem[curlist.headfield].hh.rh = avail;
	avail = curlist.headfield;
	nestptr--;
	curlist = nest[nestptr];
}
