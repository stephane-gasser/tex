#include "convtoks.h"
#include "scanint.h"
#include "gettoken.h"
#include "scanfontident.h"
#include "openlogfile.h"
#include "printint.h"
#include "printromanint.h"
#include "sprintcs.h"
#include "printchar.h"
#include "printmeaning.h"
#include "print.h"
#include "printscaled.h"
#include "begintokenlist.h"
#include "strtoks.h"
#include "texte.h"

void convtoks(void)
{
	auto c = curchr;
	smallnumber savescannerstatus;
	switch (c)
	{
		case 0:
		case 1: 
			scanint();
			break;
		case 2:
		case 3:
			savescannerstatus = scannerstatus;
			scannerstatus = 0;
			gettoken();
			scannerstatus = savescannerstatus;
			break;
		case 4: 
			scanfontident();
			break;
		case 5: 
			if (jobname == 0)
				openlogfile();
	}
	oldsetting = selector;
	selector = new_string;
	auto b = poolptr;
	switch (c)
	{
		case 0: 
			printint(curval);
			break;
		case 1: 
			printromanint(curval);
			break;
		case 2: 
			if (curcs)
				sprintcs(curcs);
			else
				printchar(curchr);
			break;
		case 3: 
			printmeaning();
			break;
		case 4:
			print(TXT(fontname[curval]));
			if (fontsize[curval] != fontdsize[curval])
			{
				print(" at ");
				printscaled(fontsize[curval]);
				print("pt");
			}
			break;
		case 5: 
			print(TXT(jobname));
	}
	selector = oldsetting;
	link(garbage) = strtoks(b);
	begintokenlist(link(temp_head), 4);
}

