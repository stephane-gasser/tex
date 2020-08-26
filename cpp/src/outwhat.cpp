#include "outwhat.h"
#include "writeout.h"
#include "packfilename.h"
#include "fichier.h"
#include "promptfilename.h"
#include "specialout.h"
#include "erreur.h"
#include "texte.h"

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
					pack_cur_name();
					while (!aopenout(writefile[j]))
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
