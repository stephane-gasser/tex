#include "runaway.h"
#include "showtokenlist.h"
#include "print.h"
#include "printnl.h"
#include "printchar.h"
#include "println.h"

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
		printchar('?');
		println();
		showtokenlist(link(p), 0, errorline-10);
	}
}
