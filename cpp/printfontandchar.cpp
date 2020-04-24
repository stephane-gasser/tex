#include "printfontandchar.h"
#include "printesc.h"
#include "printchar.h"
#include "print.h"
#include "constantes.h"

void printfontandchar(int p)
{
	if (p > memend)
		printesc(309); //CLOBBERED.
	else
	{
		if (mem[p].hh.b0 < 0 || mem[p].hh.b0 > fontmax)
		printchar('*');
		else
		printesc(hash[frozen_null_font+mem[p].hh.b0].rh);
		printchar(' ');
		print(mem[p].hh.b1);
	}
}
