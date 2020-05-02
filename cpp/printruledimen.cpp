#include "printruledimen.h"
#include "printchar.h"
#include "printscaled.h"

void printruledimen(scaled d)
{
	if (d == -0x40'00'00'00)
		printchar('*');
	else
		printscaled(d);
}
