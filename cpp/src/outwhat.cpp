#include "outwhat.h"
#include "writeout.h"
#include "packfilename.h"
#include "fichier.h"
#include "promptfilename.h"
#include "specialout.h"
#include "erreur.h"
#include "texte.h"

void outwhat(halfword p, halfword align)
{
	switch (subtype(p))
	{
		case open_node:
		case write_node:
		case close_node:
			if (!doingleaders)
			{
				smallnumber j = write_stream(p);
				if (subtype(p) == write_node)
					writeout(p, align);
				else
				{
					if (writeopen[j])
						aclose(writefile[j]);
					if (subtype(p) == close_node)
						writeopen[j] = false;
					else 
						if (j < 16)
						{
							curname = open_name(p);
							curarea = open_area(p);
							curext = open_ext(p);
							if (curext == "")
								curext = ".tex";
							pack_cur_name();
							while (!aopenout(writefile[j]))
							promptfilename("output file name", ".tex"); 
							writeopen[j] = true;
						}
				}
			}
			break;
		case special_node: 
			specialout(p);
			break;
		case language_node:
			break;
		default:
			confusion("ext4", align);
	}
}
