#include "convtoks.h"
#include "scanint.h"
#include "gettoken.h"
#include "scanfontident.h"
#include "openlogfile.h"
#include "impression.h"
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
			if (jobname == "")
				openlogfile();
	}
	oldsetting = selector;
	selector = new_string;
	auto b = poolptr;
	switch (c)
	{
		case 0: 
			print(std::to_string(curval));
			break;
		case 1: 
			printromanint(curval);
			break;
		case 2: 
			print(curcs ? scs(curcs) : std::string(1, curchr));
			break;
		case 3: 
			printmeaning();
			break;
		case 4:
			print(fontname[curval]+(fontsize[curval] != fontdsize[curval] ? " at "+asScaled(fontsize[curval])+"pt" : ""));
			break;
		case 5: 
			print(jobname);
	}
	selector = oldsetting;
	link(garbage) = strtoks(b);
	ins_list(link(temp_head));
}

