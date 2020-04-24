#include "printstyle.h"
#include "printesc.h"
#include "print.h"

void printstyle(int c)
{
	switch (c/2)
	{
		case 0: 
			printesc(860); //displaystyle
			break;
		case 1: 
			printesc(861); //textstyle
			break;
		case 2: 
			printesc(862); //scriptstyle
			break;
		case 3:
			printesc(863); //scriptscriptstyle
			break;
		default:
			print(864); //Unknown style!
	}
}
