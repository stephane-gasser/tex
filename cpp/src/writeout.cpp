#include "writeout.h"
#include "noeud.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"

constexpr int end_write_token = cs_token_flag+end_write;

void writeout(halfword p)
{
	auto q = new TokenNode(right_brace_token+'}');
	auto r = new TokenNode(end_write_token);
	q->link = r;
	ins_list(q->num);
	begintokenlist(write_tokens(p), write_text);
	q = new TokenNode(left_brace_token+'{');
	ins_list(q->num);
	int oldmode = mode;
	mode = 0;
	Token t;
	t.cs = writeloc;
	q = scantoks(false, true, t);
	t = gettoken();
	if (t.tok != end_write_token)
	{
		error("Unbalanced write command", "On this page there's a \\write with fewer real {'s than }'s.\nI can't handle that very well; good luck.");
		do
			t = gettoken();
		while (t.tok != end_write_token);
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
	print(tokenshow(defref->num)+"\n");
	flushlist(defref->num);
	selector = oldsetting;
}
