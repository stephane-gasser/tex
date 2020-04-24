#include "printmark.h"
#include "printchar.h"
#include "printesc.h"
#include "showtokenlist.h"

void printmark(int p)
{
	printchar('{');
	if (p < himemmin || p > memend)
		printesc(309); //CLOBBERED.
	else
		showtokenlist(mem[p].hh.rh, 0, maxprintline-10);
	printchar('}');
}
