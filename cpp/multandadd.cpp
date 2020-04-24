#include "multandadd.h"

scaled multandadd(int n, scaled x, scaled y, scaled maxanswer)
{
	if (n < 0)
	{
		x = -x;
		n = -n;
	}
	if (n == 0)
		return y;
	if (x <= (maxanswer-y)/n && -x <= (maxanswer+y)/n)
		return n*x+y;
	aritherror = true;
	return 0;
}
