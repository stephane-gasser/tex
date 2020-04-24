#include "xnoverd.h"

scaled xnoverd(scaled x, int n, int  d)
{
	bool positive = x >= 0;
	if (!positive)
		x = -x;
	int t = (x%32768)*n;
	int u = (x/32768)*n+t/32768;
	int v = (u%d)*32768+t%32768;
	if (u/d >= 32768)
		aritherror = true;
	else
		u = 32768*(u/d)+v/d;
	if (positive)
	{
		remainder_ = v%d;
		return u;
	}
	remainder_ = -(v%d);
	return -u;
}
