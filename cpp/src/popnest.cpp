#include "popnest.h"

void popnest(void)
{
	delete head;
	nestptr--;
	curlist = nest[nestptr];
}
