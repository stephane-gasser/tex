#include "deleteglueref.h"
#include "freenode.h"

void deleteglueref(halfword p)
{
	if (link(p) == 0)
		freenode(p, 4);
	else
		link(p)--;
}
