#include "unpackage.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"

void unpackage(halfword c, halfword align)
{
	int val = scaneightbitint(align);
	halfword p = box(val);
	if (p == 0)
		return;
	if (abs(mode) == mmode || (abs(mode) == vmode && type(p) != vlist_node) || (abs(mode) == hmode && type(p) != hlist_node))
	{
		error("Incompatible list can't be unboxed", "Sorry, Pandora. (You sneaky devil.)\nI refuse to unbox an \\hbox in vertical mode or vice versa.\nAnd I can't open any boxes in math mode.", curalign);
		return;
	}
	if (c == copy_code)
		link(tail) = copynodelist(list_ptr(p));
	else
	{
		link(tail) = list_ptr(p);
		box(val) = 0;
		freenode(p, box_node_size);
	}
	while (link(tail))
		tail = link(tail);
}
