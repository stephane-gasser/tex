#include "runaway.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"
#include "token.h"

void runaway(void)
{
	if (scannerstatus <= skipping)
		return;
	printnl("Runaway ");
	switch (scannerstatus)
	{
		case defining:
			print("definition?\n"+tokenlist(&defRef, nullptr, errorline-10));
			break;
		case matching:
		{
			TokenNode *p; 
			print("argument");
			putAfter(p, temp_head);
			print("?\n"+tokenlist(p, nullptr, errorline-10));
			break;
		}
		case aligning:
			print("preamble?\n"+tokenlist(&holdHead, nullptr, errorline-10));
			break;
		case absorbing:
			print("text?\n"+tokenlist(&defRef, nullptr, errorline-10));
	}
}
