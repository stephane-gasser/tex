#include "printskipparam.h"
#include "printesc.h"
#include "print.h"

void printskipparam(int n)
{
	switch (n)
	{
		case 0: 
			printesc(376); //lineskip
			break;
		case 1: 
			printesc(377); //baselineskip
			break;
		case 2: 
			printesc(378); //parskip
			break;
		case 3: 
			printesc(379); //abovedisplayskip
			break;
		case 4: 
			printesc(380); //belowdisplayskip
			break;
		case 5: 
			printesc(381); //abovedisplayshortskip
			break;
		case 6: 
			printesc(382); //belowdisplayshortskip
			break;
		case 7: 
			printesc(383); //leftskip
			break;
		case 8: 
			printesc(384); //rightskip
			break;
		case 9: 
			printesc(385); //topskip
			break;
		case 10: 
			printesc(386); //splittopskip
			break;
		case 11: 
			printesc(387); //tabskip
			break;
		case 12: 
			printesc(388); //spaceskip
			break;
		case 13: 
			printesc(389); //xspaceskip
			break;
		case 14: 
			printesc(390); //parfillskip
			break;
		case 15: 
			printesc(391); //thinmuskip
			break;
		case 16: 
			printesc(392); //medmuskip
			break;
		case 17: 
			printesc(393); //thickmuskip
			break;
		default: 
			print(394); //[unknown glue parameter!]
	}
}
