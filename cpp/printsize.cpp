#include "printsize.h"
#include "printesc.h"

void printsize(int s)
{
	if (s == 0)
		printesc(412); //textfont
	else 
		if (s == 16)
			printesc(413); //scriptfont
		else
		printesc(414); //scriptscriptfont
}
