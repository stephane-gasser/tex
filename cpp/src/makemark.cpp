#include "makemark.h"
#include "lecture.h"
#include "noeud.h"

void makemark(Token t)
{
	auto p = scantoks(false, true, t)->num;
	p = getnode(small_node_size);
	type(p) = mark_node;
	subtype(p) = 0; //the |subtype| is not used
	mark_ptr(p) = defref->num;
	tail_append(p);
}
