#include "printmark.h"
#include "printchar.h"
#include "printesc.h"
#include "showtokenlist.h"

void printmark(int p)
{
	printchar('{');
	if (p < himemmin || p > memend)
		printesc("CLOBBERED.");
	else
		showtokenlist(link(p), 0, maxprintline-10);
	printchar('}');
}
