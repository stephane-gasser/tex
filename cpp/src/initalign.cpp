#include "initalign.h"
#include "impression.h"
#include "erreur.h"
#include "flushmath.h"
#include "lecture.h"
#include "pushalignment.h"
#include "pushnest.h"
#include "noeud.h"
#include "alignpeek.h"
#include "texte.h"

void initalign(Token t, halfword &loop)
{
	auto savecsptr = t.cs;
	pushalignment(loop);
	alignstate = -1000000;
	if (mode == mmode && (tail != head || incompleat_noad))
	{
		error("Improper "+esc("halign")+" inside $$'s", "Displays can use special alignments (like \\eqalignno)\nonly if nothing but the alignment itself is between $$'s.\nSo I've deleted the formulas that preceded this alignment.");
		flushmath();
	}
	pushnest();
	if (mode == mmode)
	{
		mode = -1;
		incompleat_noad = nest[nestptr-2].auxfield.int_;
	}
	else 
		if (mode > 0)
		mode = -mode;
	t = scanspec(align_group, false);
	align_head->link = nullptr;
	curalign = align_head->num;
	loop = 0;
	scannerstatus = 4;
	warningindex = savecsptr;
	alignstate = -1000000;
	while (true)
	{
		auto g = new GlueNode(tab_skip_code);
		link(curalign) = g->num;
		curalign = link(curalign);
		if (t.cmd == car_ret)
			break;
		auto p = hold_head;
		p->link = nullptr;
		while (true)
		{
			t = getpreambletoken();
			if (t.cmd == mac_param)
				break;
			if ((t.cmd == tab_mark || t.cmd == out_param) && alignstate == -1000000)
				if (p == hold_head && loop == 0 && t.cmd == tab_mark)
					loop = curalign;
				else
				{
					backerror(t, "Missing # inserted in alignment preamble", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nnone, so I've put one in; maybe that will work.");
					break;
				}
			else 
				if (t.cmd != spacer || p != hold_head)
				{
					p->link = new TokenNode(t.tok);
					p = dynamic_cast<TokenNode*>(p->link);
				}
		}
		auto B = new BoxNode;
		link(curalign) = B->num;
		curalign = link(curalign);
		info(curalign) = end_span->num;
		width(curalign) = null_flag;
		u_part(curalign) = hold_head->link->num;
		p = hold_head;
		p->link = 0;
		while (true)
		{
			t = getpreambletoken();
			if (t.cmd <= out_param && t.cmd >= tab_mark && alignstate == -1000000)
				break;
			if (t.cmd == mac_param)
			{
				error("Only one # is allowed per tab", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nmore than one, so I'm ignoring all but the first.");
				continue;
			}
			p->link = new TokenNode(t.tok);
			p = dynamic_cast<TokenNode*>(p->link);
		}
		p->link = new TokenNode(end_template_token);
		p = dynamic_cast<TokenNode*>(p->link);
		v_part(curalign) = hold_head->link->num;
	}
	scannerstatus = normal;
	newsavelevel(align_group);
	if (every_cr())
		begintokenlist(every_cr(), every_cr_text);
	alignpeek(loop);
}
