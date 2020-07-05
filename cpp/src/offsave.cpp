#include "offsave.h"
#include "impression.h"
#include "backinput.h"
#include "erreur.h"
#include "getavail.h"
#include "begintokenlist.h"
#include "texte.h"

static void erreurOffsave1(void)
{
	print_err("Extra "+cmdchr(curcmd, curchr));
	helpptr = 1;
	helpline[0] = "Things are pretty mixed up, but I think the worst is over.";
	error();
}

static void erreurOffsave2(const std::string &s)
{
	print_err(s);
	helpptr = 5;
	helpline[4] = "I've inserted something that you may have forgotten.";
	helpline[3] = "(See the <inserted text> above.)";
	helpline[2] = "With luck, this will get me unwedged. But if you";
	helpline[1] = "really didn't forget anything, try typing `2' now; then";
	helpline[0] = "my insertion and my current dilemma will both disappear.";
	error();
}

void offsave(void)
{
	if (curgroup == bottom_level)
		erreurOffsave1();
	else
	{
		backinput();
		auto p = getavail();
		link(temp_head) = p;
		switch (curgroup)
		{
			case semi_simple_group:
				info(p) = cs_token_flag+frozen_end_group;
				erreurOffsave2("Missing "+esc("endgroup")+" inserted");
				break;
			case math_shift_group:
				info(p) = math_shift_token+'$';
				erreurOffsave2("Missing $ inserted");
				break;
			case math_left_group:
				info(p) = cs_token_flag+frozen_right;
				link(p) = getavail();
				p = link(p);
				info(p) = other_token+'.';
				erreurOffsave2("Missing right. inserted");
				break;
			default:
				info(p) = right_brace_token+'}';
				erreurOffsave2("Missing } inserted");
		}
		ins_list(link(temp_head));
	}
}
