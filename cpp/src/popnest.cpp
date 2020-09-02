#include "popnest.h"

void popnest(void)
{
	delete head;
	nest.pop_back();
	curlist = nest.back();
}
