#include "finalcleanup.h"
#include "openlogfile.h"
#include "endtokenlist.h"
#include "endfilereading.h"
#include "print.h"
#include "printesc.h"
#include "printnl.h"
#include "printint.h"
#include "printchar.h"
#include "printcmdchr.h"
#include "freenode.h"
#include "deletetokenref.h"
#include "deleteglueref.h"
#include "storefmtfile.h"

void finalcleanup(void)
{
	smallnumber c = curchr;
	if (jobname == "")
		openlogfile();
	while (inputptr > 0)
		if (curinput.statefield == 0)
			endtokenlist();
		else
		endfilereading();
	while (openparens > 0)
	{
		print(" )");
		openparens--;
	}
	if (curlevel > 1)
	{
		printnl("(");
		printesc("end occurred ");
		print("inside a group at level ");
		printint(curlevel-1);
		printchar(')');
	}
	while (condptr)
	{
		printnl("(");
		printesc("end occurred ");
		print("when ");
		printcmdchr(if_test, curif);
		if (ifline)
		{
			print(" on line ");
			printint(ifline);
		}
		print(" was incomplete)");
		ifline = if_line_field(condptr);
		curif = subtype(condptr);
		tempptr = condptr;
		condptr = link(condptr);
		freenode(tempptr, 2);
	}
	if (history && (history == warning_issued || interaction < error_stop_mode) && selector == 19)
	{
		selector = term_only;
		printnl("(see the transcript file for additional information)");
		selector = term_and_log;
	}
	if (c == 1)
	{
		for (c = 0; c <= 4; c++)
		if (curmark[c])
			deletetokenref(curmark[c]);
		if (lastglue != empty_flag)
			deleteglueref(lastglue);
		storefmtfile();
		return;
	}
}
