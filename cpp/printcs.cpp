#include "printcs.h"
#include "printesc.h"
#include "printchar.h"
#include "print.h"
#include "texte.h"

void printcs(int p)
{
	if (p < 514)
		if (p >= 257)
			if (p == 513) 
			{
				printesc("csname");
				printesc("endcsname");
				printchar(' ');
			}
			else
			{
				printesc(std::string(1, char(p-257)));
				if (cat_code(p-257) == letter)
					printchar(' ');
			}
		else 
			if (p < 1)
				printesc("IMPOSSIBLE.");
			else
				printchar(p-1);
	else 
		if (p >= undefined_control_sequence)
			printesc("IMPOSSIBLE.");
		else 
			if (text(p) < 0 || text(p) >= strptr)
				printesc("NONEXISTENT.");
			else
			{
				printesc(TXT(hash[p].rh));
				printchar(' ');
			}
}
