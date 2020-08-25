#include "doextension.h"
#include "noeud.h"
#include "lecture.h"
#include "outwhat.h"
#include "backinput.h"
#include "erreur.h"
#include "normmin.h"
#include "texte.h"

void doextension(Token t)
{
	int i, j;
	TokenNode *p;
	halfword q, r;
	switch (t.chr)
	{
		case open_node:
		{
			auto ww = new OpenWriteWhatsitNode;
			ww->write_stream = scanfourbitint();
			scanoptionalequals();
			scanfilename();
			ww->open_name = curname;
			ww->open_area = curarea;
			ww->open_ext = curext;
			tail_append(ww);
			break;
		}
		case write_node:
		case close_node:
		case special_node:
		{
			auto ww = new NotOpenWriteWhatsitNode(t.chr);
			ww->write_stream = 0;
			if (t.chr != special_node)
			{
				int val = scanint();
				if (val < 0)
					val = 17;
				else 
					if (val > 15)
						val = 16;
				ww->write_stream = val;
			}
			ww->write_tokens = nullptr;
			if (t.chr != close_node)
			{
				p = scantoks(false, t.chr == special_node, t);
				ww->write_tokens = defref;
			}
			tail_append(ww);
			break;
		}
		case immediate_code:
			t = getxtoken();
			if (t.cmd == extension && t.chr <= 2)
			{
				p = dynamic_cast<TokenNode*>(tail);
				doextension(t);
				outwhat(tail->num);
				flushnodelist(tail);
				tail = p;
				p->link = nullptr;
			}
			else
				backinput(t);
			break;
		case set_language_code:
			if (abs(mode) != hmode)
				reportillegalcase(t);
			else
			{
				clang = scanint();
				if (clang <= 0 || clang > 255)
						clang = 0;
				auto w = new LanguageWhatsitNode(clang);
				w->what_lhm = normmin(left_hyphen_min());
				w->what_rhm = normmin(right_hyphen_min());
				tail_append(w);
			}
			break;
		default: 
			confusion("ext1");
	}
}
