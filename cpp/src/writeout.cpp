#include "writeout.h"
#include "getavail.h"
#include "begintokenlist.h"
#include "scantoks.h"
#include "gettoken.h"
#include "impression.h"
#include "erreur.h"
#include "endtokenlist.h"
#include "flushlist.h"
#include "texte.h"

constexpr int end_write_token = cs_token_flag+end_write;

static void erreurWriteout(void)
{
	print_err("Unbalanced write command");
	helpptr = 2;
	helpline[1] = "On this page there's a \\write with fewer real {'s than }'s.";
	helpline[0] = "I can't handle that very well; good luck.";
	error();
}

void writeout(halfword p)
{
	auto q = getavail();
	info(q) = right_brace_token+'}';
	auto r = getavail();
	link(q) = r;
	info(r) = end_write_token;
	ins_list(q);
	begintokenlist(write_tokens(p), write_text);
	q = getavail();
	info(q) = left_brace_token+'{';
	ins_list(q);
	int oldmode = mode;
	mode = 0;
	curcs = writeloc;
	q = scantoks(false, true);
	gettoken();
	if (curtok != end_write_token)
	{
		erreurWriteout();
		do
			gettoken();
		while (curtok != end_write_token);
	}
	mode = oldmode;
	endtokenlist();
	auto oldsetting = selector;
	auto j = write_stream(p);
	if (writeopen[j])
		selector = j;
	else
	{
		if (j == term_only && selector == term_and_log)
			selector = log_only;
		printnl(""); 
	}
	print(tokenshow(defref)+"\n");
	flushlist(defref);
	selector = oldsetting;
}
