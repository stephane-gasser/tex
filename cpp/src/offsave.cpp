#include "offsave.h"
#include "impression.h"
#include "backinput.h"
#include "erreur.h"
#include "getavail.h"
#include "lecture.h"
#include "texte.h"

void offsave(void)
{
	if (curgroup == bottom_level)
		error("Extra "+cmdchr(curcmd, curchr), "Things are pretty mixed up, but I think the worst is over.");
	else
	{
		backinput();
		auto p = getavail();
		link(temp_head) = p;
		switch (curgroup)
		{
			case semi_simple_group:
				info(p) = cs_token_flag+frozen_end_group;
				error("Missing "+esc("endgroup")+" inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
				break;
			case math_shift_group:
				info(p) = math_shift_token+'$';
				error("Missing $ inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
				break;
			case math_left_group:
				info(p) = cs_token_flag+frozen_right;
				link(p) = getavail();
				p = link(p);
				info(p) = other_token+'.';
				error("Missing right. inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
				break;
			default:
				info(p) = right_brace_token+'}';
				error("Missing } inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
		}
		ins_list(link(temp_head));
	}
}
