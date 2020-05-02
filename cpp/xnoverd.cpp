#include "xnoverd.h"

scaled xnoverd(scaled x, int n, int d)
{
	bool positive = x >= 0;
	if (!positive)
		x = -x;
	int t = (x%0x80'00)*n;
	int u = (x/0x80'00)*n+t/0x80'00;
	int v = (u%d)*0x80'00+t%0x80'00;
	if (u/d >= 0x80'00)
		aritherror = true;
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
