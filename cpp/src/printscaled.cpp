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
	printint(s/unity);
	printchar('.');
	s = 10*(s%unity)+5;
	scaled delta = 10;
	do
	{
		if (delta > unity)
		s += 0x80'00-50000;
		printchar('0'+s/unity);
		s = 10*(s%unity);
		delta *= 10;
	} while (s > delta);
}
