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
	printint(s/0x1'00'00);
	printchar('.');
	s = 10*(s%0x1'00'00)+5;
	scaled delta = 10;
	do
	{
		if (delta > 0x1'00'00)
		s -= 17232;
		printchar('0'+s/0x1'00'00);
		s = 10*(s%0x1'00'00);
		delta *= 10;
	} while (s > delta);
}
