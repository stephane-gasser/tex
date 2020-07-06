#include "doextension.h"
#include "newwritewhatsit.h"
#include "scanoptionalequals.h"
#include "scanfilename.h"
#include "scantoks.h"
#include "newwhatsit.h"
#include "getxtoken.h"
#include "outwhat.h"
#include "flushnodelist.h"
#include "backinput.h"
#include "scanint.h"
#include "erreur.h"
#include "normmin.h"
#include "texte.h"

void doextension(void)
{
	int i, j, k;
	halfword p, q, r;
	switch (curchr)
	{
		case open_node:
			newwritewhatsit(open_node_size);
			scanoptionalequals();
			scanfilename();
			open_name(tail) = txt(curname);
			open_area(tail) = txt(curarea);
			open_ext(tail) = txt(curext);
			break;
		case write_node:
			k = curcs;
			newwritewhatsit(write_node_size);
			curcs = k;
			p = scantoks(false, false);
			write_tokens(tail) = defref;
			break;
		case close_node:
			newwritewhatsit(write_node_size);
			write_tokens(tail) = 0;
			break;
		case special_node:
			newwhatsit(special_node, write_node_size);
			write_stream(tail) = 0;
			p = scantoks(false, true);
			write_tokens(tail) = defref;
			break;
		case immediate_code:
			getxtoken();
			if (curcmd == extension && curchr <= 2)
			{
				p = tail;
				doextension();
				outwhat(tail);
				flushnodelist(tail);
				tail = p;
				link(p) = 0;
			}
			else
				backinput();
			break;
		case set_language_code:
			if (abs(mode) != hmode)
				reportillegalcase();
			else
			{
				newwhatsit(language_node, small_node_size);
				scanint();
				if (curval <= 0)
					clang = 0;
				else 
					if (curval > 255)
						clang = 0;
					else
						clang = curval;
				what_lang(tail) = clang;
				what_lhm(tail) = normmin(left_hyphen_min());
				what_rhm(tail) = normmin(right_hyphen_min());
			}
			break;
		default: 
			confusion("ext1");
	}
}
