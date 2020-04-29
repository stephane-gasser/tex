#include "printfontandchar.h"
#include "printesc.h"
#include "printchar.h"
#include "print.h"

void printfontandchar(int p)
{
	if (p > memend)
		printesc(309); //CLOBBERED.
	else
	{
		if (type(p) < 0 || type(p) > fontmax)
		printchar('*');
		else
		printesc(hash[frozen_null_font+type(p)].rh);
		printchar(' ');
		print(subtype(p));
	}
}
