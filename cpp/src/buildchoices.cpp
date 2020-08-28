#include "buildchoices.h"
#include "sauvegarde.h"
#include "formule.h"
#include "pushmath.h"
#include "lecture.h"

void buildchoices(Token t)
{
	unsave();
	auto Tail = dynamic_cast<ChoiceNode*>(tail);
	switch (savestack.back().int_)
	{
		case 0: 
			Tail->display_mlist = finmlist(nullptr);
			break;
		case 1: 
			Tail->text_mlist = finmlist(nullptr);
			break;
		case 2: 
			Tail->script_mlist = finmlist(nullptr);
			break;
		case 3:
			Tail->script_script_mlist = finmlist(nullptr);
			savestack.pop_back();
			return;
	}
	savestack.back().int_++;
	pushmath(math_choice_group);
	t = scanleftbrace();
}
