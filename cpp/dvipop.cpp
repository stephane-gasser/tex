#include "dvipop.h"
#include "dviswap.h"

void dvipop(int l)
{
	if (l == dvioffset+dviptr && dviptr > 0)
		dviptr--;
	else
		dvi_out(pop);
}
