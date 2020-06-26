#include "offsave.h"
#include "impression.h"
#include "backinput.h"
#include "error.h"
#include "getavail.h"
#include "begintokenlist.h"
#include "texte.h"

void offsave(void)
{
	if (curgroup == bottom_level)
	{
		print_err("Extra ");
		printcmdchr(curcmd, curchr);
		helpptr = 1;
		helpline[0] = "Things are pretty mixed up, but I think the worst is over.";
	}
	else
	{
		backinput();
		auto p = getavail();
		link(temp_head) = p;
		print_err("Missing ");
		switch (curgroup)
		{
			case semi_simple_group:
				info(p) = cs_token_flag+frozen_end_group;
				printesc("endgroup");
				break;
			case math_shift_group:
				info(p) = math_shift_token+'$';
				printchar('$');
				break;
			case math_left_group:
				info(p) = cs_token_flag+frozen_right;
				link(p) = getavail();
				p = link(p);
				info(p) = other_token+'.';
				printesc("right.");
				break;
			default:
				info(p) = right_brace_token+'}';
				printchar('}');
		}
		print(" inserted");
		ins_list(link(temp_head));
		{
			helpptr = 5;
			helpline[4] = "I've inserted something that you may have forgotten.";
			helpline[3] = "(See the <inserted text> above.)";
			helpline[2] = "With luck, this will get me unwedged. But if you";
			helpline[1] = "really didn't forget anything, try typing `2' now; then";
			helpline[0] = "my insertion and my current dilemma will both disappear.";
		}
	}
	error();
}
