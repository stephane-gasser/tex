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
	info(q) = right_brace*0x1'00+'}';
	auto r = getavail();
	link(q) = r;
	info(r) = cs_token_flag+end_write;
	begintokenlist(q, 4);
	begintokenlist(link(p+1), 15);
	q = getavail();
	info(q) = left_brace*0x1'00+'{';
	begintokenlist(q, 4);
	int oldmode = mode;
	mode = 0;
	curcs = writeloc;
	q = scantoks(false, true);
	gettoken();
	if (curtok != end_write+cs_token_flag)
	{
		printnl(262); //! 
		print(1296); //Unbalanced write command
		helpptr = 2;
		helpline[1] = 1297; //On this page there's a \write with fewer real {'s than }'s.
		helpline[0] = 1011; //I can't handle that very well; good luck.
		error();
		do
			gettoken();
		while (curtok != end_write+cs_token_flag);
	}
	;
	mode = oldmode;
	endtokenlist();
	auto oldsetting = selector;
	auto j = info(p+1);
	if (writeopen[j])
		selector = j;
	else
	{
		if (j == 17 && selector == term_and_log)
			selector = log_only;
		printnl(338); //
	}
	tokenshow(defref);
	println();
	flushlist(defref);
	selector = oldsetting;
}
