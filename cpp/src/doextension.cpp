#include "doextension.h"
#include "noeud.h"
#include "lecture.h"
#include "outwhat.h"
#include "erreur.h"
#include "equivalent.h"
#include "etat.h"
#include "fichier.h"
#include "getnext.h"

void doextension(char &status, Token t)
{
	switch (t.chr)
	{
		case open_node:
			tail_append(new OpenWriteWhatsitNode(status));
			break;
		case write_node:
			tail_append(new WriteNodeWhatsitNode(status, t));
			status = normal;
			break;
		case close_node:
			tail_append(new NotOpenWriteWhatsitNode(close_node, scanner.getInt(status)));
			break;
		case special_node:
			tail_append(new SpecialNodeWhatsitNode(t));
			status = normal;
			break;
		case immediate_code:
			t = scanner.getX(status);
			if (t.cmd == extension)
				switch (t.chr) // \openout / \write / \closeout
				{
					case open_node:
						OpenWriteWhatsitNode(status).outWhat();
						break;
					case write_node:
						WriteNodeWhatsitNode(status, t).outWhat();
						status = normal;
						break;
					case close_node:
						NotOpenWriteWhatsitNode(close_node, scanner.getInt(status)).outWhat();
						break;
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
				clang = scanner.getInt(status);
				if (clang <= 0 || clang > 255)
						clang = 0;
				tail_append(new LanguageWhatsitNode(clang));
			}
			break;
		default: 
			confusion("ext1");
	}
}
