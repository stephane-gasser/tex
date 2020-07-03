#include "runaway.h"
#include "impression.h"

void runaway(void)
{
	if (scannerstatus > skipping)
	{
		printnl("Runaway ");
		halfword p;
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
		print("?\n"+tokenlist(link(p), 0, errorline-10));
	}
}
