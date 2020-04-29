#include "buildchoices.h"
#include "unsave.h"
#include "finmlist.h"
#include "pushmath.h"
#include "scanleftbrace.h"

void buildchoices(void)
{
	unsave();
	auto p = finmlist(0);
	switch (savestack[saveptr-1].int_)
	{
		case 0: 
			info(curlist.tailfield+1) = p;
			break;
		case 1: 
			link(curlist.tailfield+1) = p;
			break;
		case 2: 
			info(curlist.tailfield+2) = p;
			break;
		case 3:
			link(curlist.tailfield+2) = p;
			saveptr--;
			return;
	}
	savestack[saveptr-1].int_++;
	pushmath(13);
	scanleftbrace();
}
