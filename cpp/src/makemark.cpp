#include "makemark.h"
#include "lecture.h"
#include "noeud.h"

void makemark(Token t)
{
	auto p = scantoks(false, true, t);
	p = getnode(small_node_size);
	type(p) = mark_node;
	subtype(p) = 0; //the |subtype| is not used
	mark_ptr(p) = defref;
	tail_append(p);
}
