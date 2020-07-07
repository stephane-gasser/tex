#include "makemark.h"
#include "lecture.h"
#include "getnode.h"

void makemark(void)
{
	auto p = scantoks(false, true);
	p = getnode(2);
	type(p) = mark_node;
	subtype(p) = 0;
	mark_ptr(p) = defref;
	tail_append(p);
}
