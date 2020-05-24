#include "printskipparam.h"
#include "printesc.h"
#include "print.h"

void printskipparam(int n)
{
	switch (n)
	{
		case 0: 
			printesc("lineskip");
			break;
		case 1: 
			printesc("baselineskip");
			break;
		case 2: 
			printesc("parskip");
			break;
		case 3: 
			printesc("abovedisplayskip");
			break;
		case 4: 
			printesc("belowdisplayskip");
			break;
		case 5: 
			printesc("abovedisplayshortskip");
			break;
		case 6: 
			printesc("belowdisplayshortskip");
			break;
		case 7: 
			printesc("leftskip");
			break;
		case 8: 
			printesc("rightskip");
			break;
		case 9: 
			printesc("topskip");
			break;
		case 10: 
			printesc("splittopskip");
			break;
		case 11: 
			printesc("tabskip");
			break;
		case 12: 
			printesc("spaceskip");
			break;
		case 13: 
			printesc("xspaceskip");
			break;
		case 14: 
			printesc("parfillskip");
			break;
		case 15: 
			printesc("thinmuskip");
			break;
		case 16: 
			printesc("medmuskip");
			break;
		case 17: 
			printesc("thickmuskip");
			break;
		default: 
			print("[unknown glue parameter!]");
	}
}
