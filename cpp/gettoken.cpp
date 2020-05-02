#include "gettoken.h"
#include "getnext.h"

void gettoken(void)
{
	nonewcontrolsequence = false;
	getnext();
	nonewcontrolsequence = true;
	if (curcs == 0)
		curtok = curcmd*0x1'00+curchr;
	else
		curtok = 0x0F'FF+curcs;
}
