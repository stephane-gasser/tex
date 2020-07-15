#include "buildchoices.h"
#include "unsave.h"
#include "finmlist.h"
#include "pushmath.h"
#include "lecture.h"

void buildchoices(halfword tok)
{
	unsave(tok);
	auto p = finmlist(0); // the current mlist
	switch (saved(-1))
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
	saved(-1)++;
	pushmath(math_choice_group);
	std::tie(std::ignore, std::ignore, tok) = scanleftbrace();
}
