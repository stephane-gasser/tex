#include "buildchoices.h"
#include "sauvegarde.h"
#include "formule.h"
#include "pushmath.h"
#include "lecture.h"
#include "etat.h"

void buildchoices(void)
{
	unsave();
	auto Tail = dynamic_cast<ChoiceNode*>(tail);
	switch (2*savestack.back()->int_)
	{
		case display_style: 
			Tail->display_mlist = finmlist(nullptr);
			break;
		case text_style: 
			Tail->text_mlist = finmlist(nullptr);
			break;
		case script_style: 
			Tail->script_mlist = finmlist(nullptr);
			break;
		case script_script_style:
			Tail->script_script_mlist = finmlist(nullptr);
			savestack.pop_back();
			return;
	}
	savestack.back()->int_++;
	pushmath(math_choice_group);
}
