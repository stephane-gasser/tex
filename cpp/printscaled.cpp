#include "printscaled.h"
#include "printchar.h"
#include "printint.h"

void printscaled(scaled s)
{
	if (s < 0)
	{
		printchar('-');
		s = -s;
	}
	printint(s/65536);
	printchar('.');
	s = 10*(s%65536)+5;
	scaled delta = 10;
	do
	{
		if (delta > 65536)
		s -= 17232;
		printchar('0'+s/65536);
		s = 10*(s%65536);
		delta *= 10;
	} while (s > delta);
}
