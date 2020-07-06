#include "newwhatsit.h"
#include "getnode.h"

void newwhatsit(smallnumber s, smallnumber w)
{
	auto p = getnode(w);
	type(p) = whatsit_node;
	subtype(p) = s;
	tail_append(p);
}