#include "pushnest.h"
#include "erreur.h"
#include "noeud.h"

void pushnest(void)
{
	if (nestptr > maxneststack)
	{
		maxneststack = nestptr;
		if (nestptr == nestsize)
			overflow("semantic nest size", nestsize); 
	}
	nest[nestptr++] = curlist;
	tail = head = new LinkedNode;
	prev_graf = 0;
	mode_line = line;
}
