#include "finalcleanup.h"
#include "openlogfile.h"
#include "endfilereading.h"
#include "impression.h"
#include "noeud.h"
#include "lecture.h"
#include "storefmtfile.h"
#include "deleteglueref.h"

void finalcleanup(Token t)
{
	smallnumber c = t.chr;
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
		printnl("("+esc("end")+" occurred inside a group at level "+std::to_string(curlevel-level_one)+")");
	while (condptr)
	{
		Token tk;
		tk.cmd = if_test;
		tk.chr = curif;
		printnl("("+esc("end")+" occurred when "+cmdchr(tk)+(ifline ? " on line "+std::to_string(ifline) : "")+" was incomplete)");
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
		if (lastglue)
			deleteglueref(lastglue);
		storefmtfile();
		return;
	}
}
