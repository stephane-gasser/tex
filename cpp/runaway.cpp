#include "runaway.h"
#include "showtokenlist.h"
#include "print.h"
#include "printnl.h"
#include "printchar.h"
#include "println.h"

void runaway(void)
{
	if (scannerstatus > 1)
	{
		printnl(569); //Runaway 
		halfword p;
		switch (scannerstatus)
		{
			case 2:
				print(570); //definition
				p = defref;
				break;
			case 3:
				print(571); //argument
				p = 29997;
				break;
			case 4:
				print(572); //preamble
				p = 29996;
				break;
			case 5:
				print(573); //text
				p = defref;
		}
		printchar('?');
		println();
		showtokenlist(link(p), 0, errorline-10);
	}
}
