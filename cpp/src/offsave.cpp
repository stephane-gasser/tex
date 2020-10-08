#include "offsave.h"
#include "impression.h"
#include "etat.h"
#include "erreur.h"
#include "equivalent.h"
#include "noeud.h"
#include "lecture.h"

void offsave(Token t)
{
	if (curgroup == bottom_level)
	{
		error("Extra "+cmdchr(t), "Things are pretty mixed up, but I think the worst is over.");
		return;
	}
	backinput(t);
	tempHead.list.clear();
	switch (curgroup)
	{
		case semi_simple_group:
			tempHead.list.push_back(cs_token_flag+frozen_end_group);
			error("Missing "+esc("endgroup")+" inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
			break;
		case math_shift_group:
			tempHead.list.push_back(math_shift_token+'$');
			error("Missing $ inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
			break;
		case math_left_group:
			tempHead.list.push_back(cs_token_flag+frozen_right);
			tempHead.list.push_back(other_token+'.');
			error("Missing right. inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
			break;
		default:
			tempHead.list.push_back(right_brace_token+'}');
			error("Missing } inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
	}
	ins_list(&tempHead);
}
