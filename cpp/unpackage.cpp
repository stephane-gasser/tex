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
	if (abs(curlist.modefield) == 203 || (abs(curlist.modefield) == 1 && type(p) != vlist_node) || (abs(curlist.modefield) == 102 && type(p) != hlist_node))
	{
		if (interaction == 3)
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
		link(curlist.tailfield) = copynodelist(link(p+5));
	else
	{
		link(curlist.tailfield) = link(p+5);
		box(curval) = 0;
		freenode(p, 7);
	}
	while (link(curlist.tailfield))
		curlist.tailfield = link(curlist.tailfield);
}
