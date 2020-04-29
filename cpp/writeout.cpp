#include "writeout.h"
#include "getavail.h"
#include "begintokenlist.h"
#include "scantoks.h"
#include "gettoken.h"
#include "printnl.h"
#include "println.h"
#include "print.h"
#include "error.h"
#include "endtokenlist.h"
#include "tokenshow.h"
#include "flushlist.h"

void writeout(halfword p)
{
	auto q = getavail();
	info(q) = 637;
	auto r = getavail();
	link(q) = r;
	info(r) = 6717;
	begintokenlist(q, 4);
	begintokenlist(link(p+1), 15);
	q = getavail();
	info(q) = 379;
	begintokenlist(q, 4);
	int oldmode = curlist.modefield;
	curlist.modefield = 0;
	curcs = writeloc;
	q = scantoks(false, true);
	gettoken();
	if (curtok != 6717)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1296); //Unbalanced write command
		helpptr = 2;
		helpline[1] = 1297; //On this page there's a \write with fewer real {'s than }'s.
		helpline[0] = 1011; //I can't handle that very well; good luck.
		error();
		do
			gettoken();
		while (curtok != 6717);
	}
	;
	curlist.modefield = oldmode;
	endtokenlist();
	auto oldsetting = selector;
	auto j = info(p+1);
	if (writeopen[j])
		selector = j;
	else
	{
		if (j == 17 && selector == 19)
			selector = 18;
		printnl(338); //
	}
	tokenshow(defref);
	println();
	flushlist(defref);
	selector = oldsetting;
}
