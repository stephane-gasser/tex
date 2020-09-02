#include "pushnest.h"
#include "erreur.h"
#include "noeud.h"

void pushnest(void)
{
	if (nest.size()-1 == nestsize)
		overflow("semantic nest size", nestsize); 
	nest.push_back(curlist);
	tail = head = new LinkedNode;
	prev_graf = 0;
	mode_line = line;
}
