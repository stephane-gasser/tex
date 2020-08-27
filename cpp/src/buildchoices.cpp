#include "buildchoices.h"
#include "unsave.h"
#include "finmlist.h"
#include "pushmath.h"
#include "lecture.h"

void buildchoices(Token t)
{
	unsave();
	auto p = finmlist(nullptr); // the current mlist
	auto Tail = dynamic_cast<ChoiceNode*>(tail);
	switch (saved(-1))
	{
		case 0: 
			Tail->display_mlist = p;
			break;
		case 1: 
			Tail->text_mlist = p;
			break;
		case 2: 
			Tail->script_mlist = p;
			break;
		case 3:
			Tail->script_script_mlist = p;
			saveptr--;
			return;
	}
	saved(-1)++;
	pushmath(math_choice_group);
	t = scanleftbrace();
}
