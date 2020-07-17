#include "writeout.h"
#include "getavail.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "flushlist.h"
#include "texte.h"

constexpr int end_write_token = cs_token_flag+end_write;

void writeout(halfword p, halfword align)
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
	halfword cs = writeloc;
	q = scantoks(false, true, cs, align);
	halfword tok;
	std::tie(std::ignore, std::ignore, tok, std::ignore) = gettoken(align);
	if (tok != end_write_token)
	{
		error("Unbalanced write command", "On this page there's a \\write with fewer real {'s than }'s.\nI can't handle that very well; good luck.", align);
		do
			std::tie(std::ignore, std::ignore, tok, std::ignore) = gettoken(align);
		while (tok != end_write_token);
	}
	mode = oldmode;
	endtokenlist(align);
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
