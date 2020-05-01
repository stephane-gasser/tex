#include "printcs.h"
#include "printesc.h"
#include "printchar.h"
#include "print.h"

void printcs(int p)
{
	if (p < 514)
		if (p >= 257)
			if (p == 513) 
			{
				printesc(504); //csname
				printesc(505); //endcsname
				printchar(' ');
			}
			else
			{
				printesc(p-257);
				if (cat_code(p-257) == letter)
					printchar(' ');
			}
		else 
			if (p < 1)
				printesc(506); //IMPOSSIBLE.
			else
				print(p-1);
	else 
		if (p >= 2881)
			printesc(506); //IMPOSSIBLE.
		else 
			if (hash[p].rh < 0 || hash[p].rh >= strptr)
				printesc(507); //NONEXISTENT.
			else
			{
				printesc(hash[p].rh);
				printchar(' ');
			}
}
