#include "unpackage.h"
#include "scaneightbitint.h"
#include "impression.h"
#include "erreur.h"
#include "copynodelist.h"
#include "freenode.h"
#include "texte.h"

void unpackage(void)
{
	auto c = curchr;
	scaneightbitint();
	halfword p = box(curval);
	if (p == 0)
		return;
	if (abs(mode) == mmode || (abs(mode) == vmode && type(p) != vlist_node) || (abs(mode) == hmode && type(p) != hlist_node))
	{
		error("Incompatible list can't be unboxed", "Sorry, Pandora. (You sneaky devil.)\nI refuse to unbox an \\hbox in vertical mode or vice versa.\nAnd I can't open any boxes in math mode.");
		return;
	}
	if (c == copy_code)
		link(tail) = copynodelist(list_ptr(p));
	else
	{
		link(tail) = list_ptr(p);
		box(curval) = 0;
		freenode(p, box_node_size);
	}
	while (link(tail))
		tail = link(tail);
}
