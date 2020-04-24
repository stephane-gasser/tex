#include "printint.h"
#include "printchar.h"
#include "printthedigs.h"

void printint(int n)
{
	int k = 0;
	if (n < 0) // nombre négatif
	{
		printchar('-');
		if (n > -100000000) // taille raisonnable
			n = -n;
		else // nombre super négatif => probablement une manip de vieux briscard en 32 bits [inutile]
		{
			int m = -1-n;
			n = m/10; // (-1-n)/10
			m = m%10+1; // (-1-n)%10+1
			k = 1;
			if (m < 10)
				dig[0] = m;
			else
			{
				dig[0] = 0;
				n++;
			}
		}
	}
	do
	{
		dig[k] = n%10;
		n /= 10;
		k++;
	} while (n);
	printthedigs(k);
}
