#include "sprintcs.h"
#include "printesc.h"
#include "printchar.h"
#include "texte.h"

void sprintcs(halfword p)
{
	if (p < 514)
		if (p < 257)
			printchar(p-1);
		else 
			if (p < 513)
				printesc(std::string(1, char(p-257)));
			else
			{
				printesc("csname");
				printesc("endcsname");
			}
	else
		printesc(TXT(text(p)));
		
}
