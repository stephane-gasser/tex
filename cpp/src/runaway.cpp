#include "runaway.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"

void runaway(void)
{
	if (scannerstatus > skipping)
	{
		printnl("Runaway ");
		LinkedNode *p; 
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
		print("?\n"+tokenlist(dynamic_cast<TokenNode*>(p->link), nullptr, errorline-10));
	}
}
