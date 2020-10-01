#include "runaway.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"

void runaway(void)
{
	if (scannerstatus <= skipping)
		return;
	printnl("Runaway ");
	TokenNode *p; 
	switch (scannerstatus)
	{
		case defining:
			print("definition");
			p = defref;
			break;
		case matching:
			print("argument");
			p = temp_head;
			break;
		case aligning:
			print("preamble");
			p = hold_head;
			break;
		case absorbing:
			print("text");
			p = defref;
	}
	next(p);
	print("?\n"+tokenlist(p, nullptr, errorline-10));
}
