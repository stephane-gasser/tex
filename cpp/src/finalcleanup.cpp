#include "finalcleanup.h"
#include "impression.h"
#include "noeud.h"
#include "lecture.h"
#include "fmtfile.h"
#include "deleteglueref.h"
#include "conditional.h"
#include "erreur.h"
#include "equivalent.h"
#include "fichier.h"

void finalcleanup(Token t)
{
	smallnumber c = t.chr;
	if (jobname == "")
		openlogfile();
	while (inputstack.size() > 1)
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
		printnl("("+esc("end")+" occurred when "+cmdchr(make_tok(if_test, curif))+(ifline ? " on line "+std::to_string(ifline) : "")+" was incomplete)");
		ifline = condptr->if_line_field;
		curif = condptr->subtype;
		removeNodeAtStart(condptr);
	}
	if (history && (history == warning_issued || interaction < error_stop_mode) && selector == term_and_log)
	{
		selector = term_only;
		printnl("(see the transcript file for additional information)");
		selector = term_and_log;
	}
	if (c == 1)
	{
		for (auto m: curmark)
			if (m)
				deletetokenref(m);
		if (lastglue)
			deleteglueref(lastglue);
		storefmtfile();
		return;
	}
}
