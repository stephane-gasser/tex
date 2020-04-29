#include "popnest.h"

void popnest(void)
{
	link(curlist.headfield) = avail;
	avail = curlist.headfield;
	nestptr--;
	curlist = nest[nestptr];
}
