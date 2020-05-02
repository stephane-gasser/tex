#include "makemark.h"
#include "scantoks.h"
#include "getnode.h"

void makemark(void)
{
	auto p = scantoks(false, true);
	p = getnode(2);
	type(p) = mark_node;
	subtype(p) = 0;
	mem[p+1].int_ = defref;
	tail_append(p);
}
