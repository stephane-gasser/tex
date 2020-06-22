#include "printcs.h"
#include "printesc.h"
#include "printchar.h"
#include "print.h"
#include "texte.h"

void printcs(int p)
{
	if (p < hash_base)
		if (p >= single_base)
			if (p == null_cs)
			{
				printesc("csname");
				printesc("endcsname");
				printchar(' ');
			}
			else
			{
				printesc(std::string(1, char(p-single_base)));
				if (cat_code(p-single_base) == letter)
					printchar(' ');
			}
		else 
			if (p < active_base)
				printesc("IMPOSSIBLE.");
			else
				printchar(p-active_base);
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

