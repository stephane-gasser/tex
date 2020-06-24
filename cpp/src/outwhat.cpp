#include "outwhat.h"
#include "writeout.h"
#include "packfilename.h"
#include "aclose.h"
#include "aopenout.h"
#include "promptfilename.h"
#include "specialout.h"
#include "confusion.h"
#include "texte.h"

void outwhat(halfword p)
{
	switch (subtype(p))
	{
		case 0:
		case 1:
		case 2:
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
		case 3: 
			specialout(p);
			break;
		case 4:
			break;
		default:
			confusion("ext4");
	}
}
