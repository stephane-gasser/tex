#include "calcul.h"

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
	throw ArithException();
	aritherror = true;
	return 0;
}

scaled nx_plus_y(int n, scaled x, scaled y)
{
	return multandadd(n, x, y, max_dimen);
}

scaled mu_mult(int n, scaled x, int f)
{
	return nx_plus_y(n, x, xnoverd(x, f, unity));
}

scaled mult_integers(int n, scaled x)
{
	return multandadd(n, x, 0, infinity);
}

scaled xnoverd(scaled x, int n, int d)
{
	bool positive = x >= 0;
	if (!positive)
		x = -x;
	int t = (x%0x80'00)*n;
	int u = (x/0x80'00)*n+t/0x80'00;
	int v = (u%d)*0x80'00+t%0x80'00;
	if (u/d >= 0x80'00)
	{
		throw ArithException();
		aritherror = true;
	}
	else
		u = 0x80'00*(u/d)+v/d;
	if (positive)
	{
		remainder_ = v%d;
		return u;
	}
	remainder_ = -(v%d);
	return -u;
}

scaled xovern(scaled x, int n)
{
	bool negative = false;
	if (n == 0)
	{
		throw ArithException();
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

int half(int x)
{
	if (x%2)
		return (x+1)/2;
	return x/2;
}
