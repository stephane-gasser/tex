#include "gettoken.h"
#include "getnext.h"

void gettoken(void)
{
	nonewcontrolsequence = false;
	getnext();
	nonewcontrolsequence = true;
	if (curcs == 0)
		curtok = curcmd*256+curchr;
	else
		curtok = 4095+curcs;
}
