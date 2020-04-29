#include "printwritewhatsit.h"
#include "printesc.h"
#include "printint.h"
#include "printchar.h"

void printwritewhatsit(strnumber s, halfword p)
{
	printesc(s);
	if (info(p+1) < 16)
		printint(info(p+1));
	else 
		if (info(p+1) == 16)
			printchar('*');
		else
			printchar('-');
}
