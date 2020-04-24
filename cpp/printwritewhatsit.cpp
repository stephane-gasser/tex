#include "printwritewhatsit.h"
#include "printesc.h"
#include "printint.h"
#include "printchar.h"

void printwritewhatsit(strnumber s, halfword p)
{
	printesc(s);
	if (mem[p+1].hh.lh < 16)
		printint(mem[p+1].hh.lh);
	else 
		if (mem[p+1].hh.lh == 16)
			printchar('*');
		else
			printchar('-');
}
