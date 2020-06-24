#include "multandadd.h"
#include "xnoverd.h"

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

scaled nx_plus_y(int n, scaled x, scaled y)
{
	return multandadd(n, x, y, max_dimen);
}

scaled mu_mult(int n, scaled x)
{
	return nx_plus_y(n, x, xnoverd(x, f, unity));
}

scaled mult_integers(int n, scaled x)
{
	return multandadd(n, x, 0, infinity);
}
