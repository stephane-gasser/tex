#include "printsize.h"
#include "printesc.h"

void printsize(int s)
{
	if (s == 0)
		printesc("textfont");
	else 
		if (s == 16)
			printesc("scriptfont");
		else
		printesc("scriptscriptfont");
}
