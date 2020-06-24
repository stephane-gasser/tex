#include "printhex.h"
#include "printchar.h"
#include "printthedigs.h"

void printhex(int n)
{
	int k = 0;
	printchar('"');
	do
	{
		dig[k] = n%16;
		n /= 16;
		k++;
	}
	while (n);
	printthedigs(k);
}
