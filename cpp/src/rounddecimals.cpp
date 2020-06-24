#include "rounddecimals.h"

scaled rounddecimals(smallnumber k)
{
	int a = 0;
	while (k > 0)
	{
		k--;
		a = (a+dig[k]*two)/10;
	}
	return (a+1)/2;
}
