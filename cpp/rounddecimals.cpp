#include "rounddecimals.h"

scaled rounddecimals(smallnumber k)
{
	int a = 0;
	while (k > 0)
	{
		k--;
		a = (a+dig[k]*131072)/10; // 131'072 = 0x2'00'00
	}
	return (a+1)/2;
}
