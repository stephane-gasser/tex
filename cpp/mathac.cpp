#include "mathac.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"
#include "getnode.h"
#include "scanfifteenbitint.h"
#include "scanmath.h"

void mathac(void)
{
	if (curcmd == 45)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1138); //Please use 
		printesc(523); //mathaccent
		print(1139); // for accents in math mode
		helpptr = 2;
		helpline[1] = 1140; //I'm changing \accent to \mathaccent here; wish me luck.
		helpline[0] = 1141; //(Accents are not the same in formulas as they are in text.)
		error();
	}
	link(curlist.tailfield) = getnode(5);
	curlist.tailfield = link(curlist.tailfield);
	type(curlist.tailfield) = 28;
	subtype(curlist.tailfield) = 0;
	mem[curlist.tailfield+1].hh = emptyfield;
	mem[curlist.tailfield+3].hh = emptyfield;
	mem[curlist.tailfield+2].hh = emptyfield;
	link(curlist.tailfield+4) = 1;
	scanfifteenbitint();
	subtype(curlist.tailfield+4) = curval%256;
	if (curval >= 28672 && eqtb[5307].int_ >= 0 && eqtb[5307].int_ < 16)
		type(curlist.tailfield+4) = eqtb[5307].int_;
	else
		type(curlist.tailfield+4) = (curval/256)%16;
	scanmath(curlist.tailfield+1);
}
