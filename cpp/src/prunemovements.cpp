#include "prunemovements.h"
#include "noeud.h"

void prunemovements(int l)
{
	while (downptr)
	{
		if (location(downptr) < l)
			break;
		auto p = downptr;
		downptr = link(p);
		freenode(p, movement_node_size);
	}
	while (rightptr)
	{
		if (location(rightptr) < l)
			break;
		auto p = rightptr;
		rightptr = link(p);
		freenode(p, movement_node_size);
	}
}

