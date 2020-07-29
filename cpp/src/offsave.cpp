#include "offsave.h"
#include "impression.h"
#include "backinput.h"
#include "erreur.h"
#include "noeud.h"
#include "lecture.h"
#include "texte.h"

void offsave(Token t)
{
	if (curgroup == bottom_level)
	{
		error("Extra "+cmdchr(t), "Things are pretty mixed up, but I think the worst is over.");
		return;
	}
	backinput(t);
	TokenNode *p;
	switch (curgroup)
	{
		case semi_simple_group:
			p = new TokenNode(cs_token_flag+frozen_end_group);
			error("Missing "+esc("endgroup")+" inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
			break;
		case math_shift_group:
			p = new TokenNode(math_shift_token+'$');
			error("Missing $ inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
			break;
		case math_left_group:
			p = new TokenNode(cs_token_flag+frozen_right);
			p->link = new TokenNode(other_token+'.');
			p = dynamic_cast<TokenNode*>(p->link);
			error("Missing right. inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
			break;
		default:
			p = new TokenNode(right_brace_token+'}');
			error("Missing } inserted", "I've inserted something that you may have forgotten.\n(See the <inserted text> above.)\nWith luck, this will get me unwedged. But if you\nreally didn't forget anything, try typing `2' now; then\nmy insertion and my current dilemma will both disappear.");
	}
	temp_head->link = dynamic_cast<LinkedNode*>(p);
	ins_list(temp_head->link->num); 
}
