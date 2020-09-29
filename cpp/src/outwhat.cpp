#include "outwhat.h"
#include "fichier.h"
#include "dvi.h"
#include "erreur.h"
#include "chaine.h"
#include "impression.h"
#include "lecture.h"

constexpr int end_write_token = cs_token_flag+end_write;

static void writeout(NotOpenWriteWhatsitNode *p)
{
	auto q = new TokenNode(right_brace_token+'}');
	q->link = new TokenNode(end_write_token);
	ins_list(q);
	begintokenlist(p->write_tokens, write_text);
	ins_list(new TokenNode(left_brace_token+'{'));
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
	auto j = p->write_stream;
	if (writeopen[j])
		selector = j;
	else
	{
		if (j == term_only && selector == term_and_log)
			selector = log_only;
		printnl("");
	}
	print(tokenshow(defref)+"\n");
	flushnodelist(defref);
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
	auto t = p->write_tokens;
	next(t);
	for (auto c: tokenlist(t, 0, poolsize))
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

void NotOpenWriteWhatsitNode::out(void)
{
	switch (subtype)
	{
		case write_node:
			writeout(this);
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
