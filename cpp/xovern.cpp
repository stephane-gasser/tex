#include "xovern.h"

scaled xovern(scaled x, int n)
{
	bool negative = false;
	if (n == 0)
	{
		aritherror = true;
		remainder_ = x;
		return 0;
	}
	if (n < 0)
	{
		x = -x;
		n = -n;
		negative = true;
	}
	if (x >= 0)
	{
		remainder_ = negative ? -x%n : x%n;
		return x/n;
	}
	remainder_ = negative ? (-x)%n : -((-x)%n);
	return -((-x)/n);
}

