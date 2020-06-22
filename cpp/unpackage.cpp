#include "unpackage.h"
#include "scaneightbitint.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
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
		printnl("! ");
		print("Incompatible list can't be unboxed");
		helpptr = 3;
		helpline[2] = "Sorry, Pandora. (You sneaky devil.)";
		helpline[1] = "I refuse to unbox an \\hbox in vertical mode or vice versa.";
		helpline[0] = "And I can't open any boxes in math mode.";
		error();
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
