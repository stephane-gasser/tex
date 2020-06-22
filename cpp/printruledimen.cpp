#include "printruledimen.h"
#include "printchar.h"
#include "printscaled.h"

void printruledimen(scaled d)
{
	if (is_running(d))
		printchar('*');
	else
		printscaled(d);
}
