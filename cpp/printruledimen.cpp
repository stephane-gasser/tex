#include "printruledimen.h"
#include "printchar.h"
#include "printscaled.h"

void printruledimen(scaled d)
{
	if (d == -1073741824)
		printchar('*');
	else
		printscaled(d);
}
