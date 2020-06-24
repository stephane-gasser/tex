#include "printglue.h"
#include "print.h"
#include "printchar.h"
#include "printscaled.h"
#include "texte.h"

void printglue(scaled d, int order, const std::string &s)
{
	printscaled(d);
	if (order < 0 || order > 3)
		print("foul");
	else 
		if (order > 0)
		{
			print("fil");
			for (;order > 1; order--)
				printchar('l');
		}
		else 
			if (txt(s))
				print(s);
}
