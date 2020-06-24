#include "printthedigs.h"
#include "printchar.h"

void printthedigs(eightbits k)
{
	while (k > 0)
	{
		k--;
		if (dig[k] < 10)
			printchar('0'+dig[k]);
		else
			printchar('A'+dig[k]-10);
	}
}
