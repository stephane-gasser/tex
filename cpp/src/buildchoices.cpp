#include "buildchoices.h"
#include "unsave.h"
#include "finmlist.h"
#include "pushmath.h"
#include "lecture.h"

void buildchoices(void)
{
	unsave();
	auto p = finmlist(0); // the current mlist
	switch (savestack[saveptr-1].int_)
	{
		case 0: 
			display_mlist(tail) = p;
			break;
		case 1: 
			text_mlist(tail) = p;
			break;
		case 2: 
			script_mlist(tail) = p;
			break;
		case 3:
			script_script_mlist(tail) = p;
			saveptr--;
			return;
	}
	savestack[saveptr-1].int_++;
	pushmath(math_choice_group);
	scanleftbrace();
}
