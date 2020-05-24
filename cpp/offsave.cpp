#include "offsave.h"
#include "printnl.h"
#include "printcmdchr.h"
#include "print.h"
#include "backinput.h"
#include "error.h"
#include "printesc.h"
#include "getavail.h"
#include "printchar.h"
#include "begintokenlist.h"
#include "texte.h"

void offsave(void)
{
	halfword p;
	if (curgroup == 0)
	{
		printnl("! ");
		print("Extra ");
		printcmdchr(curcmd, curchr);
		helpptr = 1;
		helpline[0] = txt("Things are pretty mixed up, but I think the worst is over.");
		error();
	}
	else
	{
		backinput();
		p = getavail();
		link(temp_head) = p;
		printnl("! ");
		print("Missing ");
		switch (curgroup)
		{
			case 14:
				info(p) = frozen_end_group+cs_token_flag;
				printesc("endgroup");
				break;
			case 15:
				info(p) = math_shift*0x01'FF+'$';
				printchar('$');
				break;
			case 16:
				info(p) = frozen_right+cs_token_flag;
				link(p) = getavail();
				p = link(p);
				info(p) = other_char*0x01'FF+'.';
				printesc("right.");
				break;
			default:
				info(p) = right_brace*0x01'00+'}';
				printchar('}');
		}
		print(" inserted");
		begintokenlist(link(temp_head), 4);
		{
			helpptr = 5;
			helpline[4] = txt("I've inserted something that you may have forgotten.");
			helpline[3] = txt("(See the <inserted text> above.)");
			helpline[2] = txt("With luck, this will get me unwedged. But if you");
			helpline[1] = txt("really didn't forget anything, try typing `2' now; then");
			helpline[0] = txt("my insertion and my current dilemma will both disappear.");
		}
		error();
	}
}
