#include "makemark.h"
#include "lecture.h"
#include "noeud.h"

void makemark(halfword cs)
{
	auto p = scantoks(false, true, cs);
	p = getnode(small_node_size);
	type(p) = mark_node;
	subtype(p) = 0; //the |subtype| is not used
	mark_ptr(p) = defref;
	tail_append(p);
}
