#include "dvipop.h"
#include "dviswap.h"

void dvipop(int l)
{
	if (l == dvioffset+dviptr && dviptr > 0)
		dviptr--;
	else
	{
		dvibuf[dviptr++] = pop;
		if (dviptr == dvilimit)
			dviswap();
	}
}
