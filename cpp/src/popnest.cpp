#include "popnest.h"

void popnest(void)
{
	link(head) = avail;
	avail = head;
	nestptr--;
	curlist = nest[nestptr];
}
