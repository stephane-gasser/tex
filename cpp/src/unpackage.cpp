#include "unpackage.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"

void unpackage(halfword c)
{
	int val = scaneightbitint();
	halfword p = box(val);
	if (p == 0)
		return;
	if (abs(mode) == mmode || (abs(mode) == vmode && type(p) != vlist_node) || (abs(mode) == hmode && type(p) != hlist_node))
	{
		error("Incompatible list can't be unboxed", "Sorry, Pandora. (You sneaky devil.)\nI refuse to unbox an \\hbox in vertical mode or vice versa.\nAnd I can't open any boxes in math mode.");
		return;
	}
	if (c == copy_code)
		tail->link->num = copynodelist(list_ptr(p));
	else
	{
		tail->link->num = list_ptr(p);
		box(val) = 0;
		freenode(p, box_node_size);
	}
	while (tail->link)
		tail = tail->link;
}
