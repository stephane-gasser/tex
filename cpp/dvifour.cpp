#include "dvifour.h"
#include "dviswap.h"

void dvifour(int x)
{
	if (x >= 0)
	{
		dvibuf[dviptr++] = x/16777216;
		if (dviptr == dvilimit)
			dviswap();
	}
	else
	{
		x += 1073741824;
		x += 1073741824; // deux fois
		dvibuf[dviptr++] = (x/16777216)+128;
		if (dviptr == dvilimit)
			dviswap();
	}
	x %= 16777216;
	{
		dvibuf[dviptr++] = x/65536;
		if (dviptr == dvilimit)
			dviswap();
	}
	x %= 65536;
	dvibuf[dviptr++] = x/256;
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = x%256;
	if (dviptr == dvilimit)
		dviswap();
}
