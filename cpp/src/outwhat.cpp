#include "outwhat.h"
#include "writeout.h"
#include "fichier.h"
#include "dvi.h"
#include "erreur.h"
#include "makestring.h"
#include "impression.h"

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
	for (auto c: tokenlist(dynamic_cast<TokenNode*>(p->write_tokens->link), 0, poolsize/*-poolptr*/))
		dvi_out(c);
}

void outwhat(WhatsitNode *P)
{
	switch (P->subtype)
	{
		case open_node: 
			if (!doingleaders)
			{
				auto Q = dynamic_cast<OpenWriteWhatsitNode*>(P);
				smallnumber j = Q->write_stream;
				if (writeopen[j])
					aclose(writefile[j]);
				if (j < 16)
				{
					curname = Q->open_name;
					curarea = Q->open_area;
					curext = Q->open_ext;
					if (curext == "")
						curext = ".tex";
					while (!aopenout(writefile[j], nameoffile = pack_cur_name()))
						promptfilename("output file name", ".tex"); 
					writeopen[j] = true;
				}
			}
			break;
		case write_node:
			if (!doingleaders)
			{
				auto Q = dynamic_cast<NotOpenWriteWhatsitNode*>(P);
				smallnumber j = Q->write_stream;
				writeout(Q);
			}
			break;
		case close_node:
			if (!doingleaders)
			{
				auto Q = dynamic_cast<NotOpenWriteWhatsitNode*>(P);
				smallnumber j = Q->write_stream;
				if (writeopen[j])
					aclose(writefile[j]);
				writeopen[j] = false;
			}
			break;
		case special_node: 
			specialout(dynamic_cast<NotOpenWriteWhatsitNode*>(P));
			break;
		case language_node:
			break;
		default:
			confusion("ext4");
	}
}
