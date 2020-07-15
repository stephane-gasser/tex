#include "doextension.h"
#include "noeud.h"
#include "lecture.h"
#include "outwhat.h"
#include "backinput.h"
#include "erreur.h"
#include "normmin.h"
#include "texte.h"

void doextension(halfword chr, halfword cs)
{
	int i, j, k;
	halfword p, q, r;
	halfword tok;
	eightbits cmd;
	switch (chr)
	{
		case open_node:
			newwritewhatsit(open_node_size, chr);
			scanoptionalequals();
			scanfilename();
			open_name(tail) = txt(curname);
			open_area(tail) = txt(curarea);
			open_ext(tail) = txt(curext);
			break;
		case write_node:
			k = cs;
			newwritewhatsit(write_node_size, chr);
			cs = k;
			p = scantoks(false, false, cs);
			write_tokens(tail) = defref;
			break;
		case close_node:
			newwritewhatsit(write_node_size, chr);
			write_tokens(tail) = 0;
			break;
		case special_node:
			newwhatsit(special_node, write_node_size);
			write_stream(tail) = 0;
			p = scantoks(false, true, cs);
			write_tokens(tail) = defref;
			break;
		case immediate_code:
			std::tie(cmd, chr, tok, cs) = getxtoken();
			if (cmd == extension && chr <= 2)
			{
				p = tail;
				doextension(chr, cs);
				outwhat(tail);
				flushnodelist(tail);
				tail = p;
				link(p) = 0;
			}
			else
				backinput(tok);
			break;
		case set_language_code:
			if (abs(mode) != hmode)
				reportillegalcase(cmd, chr);
			else
			{
				newwhatsit(language_node, small_node_size);
				clang = scanint();
				if (clang <= 0 || clang > 255)
						clang = 0;
				what_lang(tail) = clang;
				what_lhm(tail) = normmin(left_hyphen_min());
				what_rhm(tail) = normmin(right_hyphen_min());
			}
			break;
		default: 
			confusion("ext1");
	}
}
