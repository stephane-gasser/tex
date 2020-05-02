#include "xtoken.h"
#include "expand.h"
#include "getnext.h"

void xtoken(void)
{
	while (curcmd > max_command)
	{
		expand();
		getnext();
	}
	if (curcs == 0)
		curtok = curcmd*0x1'00+curchr;
	else
		curtok = 0x0F'FF+curcs;
}
