#include "dvipop.h"
#include "dviswap.h"

void dvipop(int l)
{
	if (l == dvioffset+dviptr && dviptr > 0)
		dviptr--;
	else
	{
		dvibuf[dviptr++] = 142;
		if (dviptr == dvilimit)
			dviswap();
	}
}
