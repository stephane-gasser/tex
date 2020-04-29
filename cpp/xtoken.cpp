#include "xtoken.h"
#include "expand.h"
#include "getnext.h"

void xtoken(void)
{
	while (curcmd > 100)
	{
		expand();
		getnext();
	}
	if (curcs == 0)
		curtok = curcmd*256+curchr;
	else
		curtok = 4095+curcs;
}
