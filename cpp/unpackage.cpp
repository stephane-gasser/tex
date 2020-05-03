#include "unpackage.h"
#include "scaneightbitint.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "copynodelist.h"
#include "freenode.h"

void unpackage(void)
{
	auto c = curchr;
	scaneightbitint();
	halfword p = box(curval);
	if (p == 0)
		return;
	if (abs(mode) == mmode || (abs(mode) == vmode && type(p) != vlist_node) || (abs(mode) == hmode && type(p) != hlist_node))
	{
		printnl(262); //! 
		print(1096); //Incompatible list can't be unboxed
		helpptr = 3;
		helpline[2] = 1097; //Sorry, Pandora. (You sneaky devil.)
		helpline[1] = 1098; //I refuse to unbox an \hbox in vertical mode or vice versa.
		helpline[0] = 1099; //And I can't open any boxes in math mode.
		error();
		return;
	}
	if (c == 1)
		link(tail) = copynodelist(link(p+5));
	else
	{
		link(tail) = link(p+5);
		box(curval) = 0;
		freenode(p, 7);
	}
	while (link(tail))
		tail = link(tail);
}
