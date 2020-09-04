#include "popnest.h"
#include "noeud.h"

void popnest(void)
{
	delete head;
	nest.pop_back();
	curlist = nest.back();
}
