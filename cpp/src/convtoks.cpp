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
		case number_code:
		case roman_numeral_code: 
			scanint();
			break;
		case string_code:
		case meaning_code:
			savescannerstatus = scannerstatus;
			scannerstatus = 0;
			gettoken();
			scannerstatus = savescannerstatus;
			break;
		case font_name_code: 
			scanfontident();
			break;
		case job_name_code: 
			if (jobname == "")
				openlogfile();
	}
	oldsetting = selector;
	selector = new_string;
	auto b = poolptr;
	switch (c)
	{
		case number_code: 
			print(std::to_string(curval));
			break;
		case roman_numeral_code: 
			print(romanint(curval));
			break;
		case string_code: 
			print(curcs ? scs(curcs) : std::string(1, curchr));
			break;
		case meaning_code: 
			print(meaning());
			break;
		case font_name_code:
			print(fontname[curval]+(fontsize[curval] != fontdsize[curval] ? " at "+asScaled(fontsize[curval])+"pt" : ""));
			break;
		case job_name_code: 
			print(jobname);
	}
	selector = oldsetting;
	link(garbage) = strtoks(b);
	ins_list(link(temp_head));
}

