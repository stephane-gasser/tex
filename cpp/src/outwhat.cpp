#include "outwhat.h"
#include "writeout.h"
#include "packfilename.h"
#include "fichier.h"
#include "promptfilename.h"
#include "specialout.h"
#include "confusion.h"
#include "texte.h"

void outwhat(halfword p)
{
	switch (subtype(p))
	{
		case open_node:
		case write_node:
		case close_node:
			if (!doingleaders)
			{
				smallnumber j = info(p+1);
				if (subtype(p) == 1)
					writeout(p);
				else
				{
					if (writeopen[j])
						aclose(writefile[j]);
					if (subtype(p) == 2)
						writeopen[j] = false;
					else 
						if (j < 16)
						{
							curname = link(p+1);
							curarea = info(p+2);
							curext = link(p+2);
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
			confusion("ext4");
	}
}
