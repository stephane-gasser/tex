#include "printstyle.h"
#include "printesc.h"
#include "print.h"

void printstyle(int c)
{
	switch (c/2)
	{
		case 0: 
			printesc("displaystyle");
			break;
		case 1: 
			printesc("textstyle");
			break;
		case 2: 
			printesc("scriptstyle");
			break;
		case 3:
			printesc("scriptscriptstyle");
			break;
		default:
			print("Unknown style!");
	}
}
