#include "doextension.h"
#include "noeud.h"
#include "lecture.h"
#include "outwhat.h"
#include "backinput.h"
#include "erreur.h"
#include "equivalent.h"
#include "fichier.h"

void doextension(Token t)
{
	switch (t.chr)
	{
		case open_node:
		{
			auto ww = new OpenWriteWhatsitNode(scanfourbitint());
			scanoptionalequals();
			scanfilename();
			ww->open_name = curname;
			ww->open_area = curarea;
			ww->open_ext = curext;
			tail_append(ww);
			break;
		}
		case write_node:
		{
			auto ww = new NotOpenWriteWhatsitNode(write_node, scanint());
			scanNonMacroToks(t);
			ww->write_tokens = &defRef;
			tail_append(ww);
			break;
		}
		case close_node:
		{
			auto ww = new NotOpenWriteWhatsitNode(close_node, scanint());
			ww->write_tokens = nullptr;
			tail_append(ww);
			break;
		}
		case special_node:
		{
			auto ww = new NotOpenWriteWhatsitNode(special_node, 0);
			scanNonMacroToksExpand(t);
			ww->write_tokens = &defRef;
			tail_append(ww);
			break;
		}
		case immediate_code:
			t = getxtoken();
			if (t.cmd == extension)
				switch (t.chr) // \openout / \write / \closeout
				{
					case open_node:
					{
						auto p = tail;
						auto ww = new OpenWriteWhatsitNode(scanfourbitint());
						scanoptionalequals();
						scanfilename();
						ww->open_name = curname;
						ww->open_area = curarea;
						ww->open_ext = curext;
						tail_append(ww);
						outwhat(ww);
						flushnodelist(tail);
						tail = p;
						tail->link = nullptr;
						break;
					}
					case write_node:
					{
						auto p = tail;
						auto ww = new NotOpenWriteWhatsitNode(write_node, scanint());
						scanNonMacroToks(t);
						ww->write_tokens = &defRef;
						tail_append(ww);
						outwhat(ww);
						flushnodelist(tail);
						tail = p;
						tail->link = nullptr;
						break;
					}
					case close_node:
					{
						auto p = tail;
						auto ww = new NotOpenWriteWhatsitNode(close_node, scanint());
						tail_append(ww);
						outwhat(ww);
						flushnodelist(tail);
						tail = p;
						tail->link = nullptr;
						break;
					}
					default:
						backinput(t);
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
				tail_append(new LanguageWhatsitNode(clang));
			}
			break;
		default: 
			confusion("ext1");
	}
}
