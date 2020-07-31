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
			newwritewhatsit(open_node_size, t);
			scanoptionalequals();
			scanfilename();
			open_name(tail->num) = txt(curname);
			open_area(tail->num) = txt(curarea);
			open_ext(tail->num) = txt(curext);
			break;
		case write_node:
			newwritewhatsit(write_node_size, t);
			p = scantoks(false, false, t);
			write_tokens(tail->num) = defref->num;
			break;
		case close_node:
			newwritewhatsit(write_node_size, t);
			write_tokens(tail->num) = 0;
			break;
		case special_node:
			newwhatsit(special_node, write_node_size);
			write_stream(tail->num) = 0;
			p = scantoks(false, true, t);
			write_tokens(tail->num) = defref->num;
			break;
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
				newwhatsit(language_node, small_node_size);
				clang = scanint();
				if (clang <= 0 || clang > 255)
						clang = 0;
				what_lang(tail->num) = clang;
				what_lhm(tail->num) = normmin(left_hyphen_min());
				what_rhm(tail->num) = normmin(right_hyphen_min());
			}
			break;
		default: 
			confusion("ext1");
	}
}
