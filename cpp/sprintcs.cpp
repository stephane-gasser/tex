#include "sprintcs.h"
#include "printesc.h"
#include "print.h"

void sprintcs(halfword p)
{
	if (p < 514)
		if (p < 257)
			print(p-1);
		else 
			if (p < 513)
				printesc(p-257);
			else
			{
				printesc(504); //csname
				printesc(505); //endcsname
			}
	else
		printesc(hash[p].rh);
}
