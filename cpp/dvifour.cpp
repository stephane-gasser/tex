#include "dvifour.h"
#include "dviswap.h"

void dvifour(int x)
{
	if (x >= 0)
	{
		dvibuf[dviptr++] = x/0x1'00'00'00;
		if (dviptr == dvilimit)
			dviswap();
	}
	else
	{
		x += 0x80'00'00'00;
		dvibuf[dviptr++] = (x/0x1'00'00'00)+0x80;
		if (dviptr == dvilimit)
			dviswap();
	}
	x %= 0x1'00'00'00;
	{
		dvibuf[dviptr++] = x/0x1'00'00;
		if (dviptr == dvilimit)
			dviswap();
	}
	x %= 0x1'00'00;
	dvibuf[dviptr++] = x/0x1'00;
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = x%0x1'00;
	if (dviptr == dvilimit)
		dviswap();
}
