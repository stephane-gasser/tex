#include "printglue.h"
#include "print.h"
#include "printchar.h"
#include "printscaled.h"

void printglue(scaled d, int order, strnumber s)
{
	printscaled(d);
	if (order < 0 || order > 3)
		print(310); //foul
	else 
		if (order > 0)
		{
			print(311); //fil
			for (;order > 1; order--)
				printchar('l');
		}
		else 
			if (s)
				print(s);
}
