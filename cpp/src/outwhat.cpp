#include "outwhat.h"
#include "fichier.h"
#include "dvi.h"
#include "erreur.h"
#include "chaine.h"
#include "impression.h"
#include "lecture.h"
#include "etat.h"
#include "initprim.h"
#include "getnext.h"

constexpr int end_write_token = cs_token_flag+end_write;

static void writeout(char status, NotOpenWriteWhatsitNode *p)
{
	TokenList head;
	head.list.push_back(right_brace_token+'}');
	head.list.push_back(end_write_token);
	ins_list(&head);
	beginTokenListAboveMacro(p->write_tokens, write_text);
	head.list.clear();
	head.list.push_back(left_brace_token+'{');
	ins_list(&head);
	int oldmode = mode;
	mode = 0;
	Token t;
	t.cs = writeloc;
	scanNonMacroToksExpand(status, t);
	t = scanner.get(status);
	if (t.tok != end_write_token)
	{
		error("Unbalanced write command", "On this page there's a \\write with fewer real {'s than }'s.\nI can't handle that very well; good luck.");
		do
			t = scanner.get(status);
		while (t.tok != end_write_token);
	}
	mode = oldmode;
	endtokenlist();
	auto oldsetting = selector;
	auto j = p->write_stream;
	if (writeopen[j])
		selector = j;
	else
	{
		if (j == term_only && selector == term_and_log)
			selector = log_only;
		print("\r");
	}
	print(tokenshow(&defRef)+"\n");
	defRef.list.clear();
	selector = oldsetting;
}

static void specialout(NotOpenWriteWhatsitNode *p)
{
	synch_h();
	synch_v();
	if (cur_length() < 256)
	{
		dvi_out(xxx1);
		dvi_out(cur_length());
	}
	else
	{
		dvi_out(xxx4);
		dvifour(cur_length());
	}
	for (auto c: tokenlist(p->write_tokens, poolsize))
		dvi_out(c);
}

void OpenWriteWhatsitNode::out(void)
{
	if (writeopen[write_stream])
		aclose(writefile[write_stream]);
	if (write_stream < 16)
	{
		curname = open_name;
		curarea = open_area;
		curext = open_ext;
		if (curext == "")
			curext = ".tex";
		while (!aopenout(writefile[write_stream], nameoffile = pack_cur_name()))
			promptfilename("output file name", ".tex"); 
		writeopen[write_stream] = true;
	}
}

void NotOpenWriteWhatsitNode::out(char status)
{
	switch (subtype)
	{
		case write_node:
			writeout(status, this);
			break;
		case close_node:
			if (writeopen[write_stream])
				aclose(writefile[write_stream]);
			writeopen[write_stream] = false;
			break;
		case special_node:
			specialout(this);
	}
}

void outwhat(WhatsitNode *w)
{
	switch (w->subtype)
	{
		case open_node: 
		case write_node:
		case close_node:
		case special_node: 
			if (!doingleaders)
				w->out();
			break;
		case language_node:
			break;
		default:
			confusion("ext4");
	}
}
