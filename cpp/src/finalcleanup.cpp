#include "finalcleanup.h"
#include "openlogfile.h"
#include "endtokenlist.h"
#include "endfilereading.h"
#include "impression.h"
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
		if (state == token_list)
			endtokenlist();
		else
			endfilereading();
	while (openparens > 0)
	{
		print(" )");
		openparens--;
	}
	if (curlevel > level_one)
	{
		printnl("(");
		printesc("end occurred ");
		print("inside a group at level ");
		printint(curlevel-level_one);
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
		freenode(tempptr, if_node_size);
	}
	if (history && (history == warning_issued || interaction < error_stop_mode) && selector == term_and_log)
	{
		selector = term_only;
		printnl("(see the transcript file for additional information)");
		selector = term_and_log;
	}
	if (c == 1)
	{
		for (c = top_mark_code; c <= split_bot_mark_code; c++)
		if (curmark[c])
			deletetokenref(curmark[c]);
		if (lastglue != empty_flag)
			deleteglueref(lastglue);
		storefmtfile();
		return;
	}
}
