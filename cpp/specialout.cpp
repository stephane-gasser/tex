#include "specialout.h"
#include "movement.h"
#include "showtokenlist.h"
#include "overflow.h"
#include "dviswap.h"
#include "dvifour.h"

void specialout(halfword p)
{
	if (curh != dvih)
	{
		movement(curh-dvih, 143);
		dvih = curh;
	}
	if (curv != dviv)
	{
		movement(curv-dviv, 157);
		dviv = curv;
	}
	auto oldsetting = selector;
	selector = new_string;
	showtokenlist(link(link(p+1)), 0, poolsize-poolptr);
	selector = oldsetting;
	if (poolptr+1 > poolsize)
		overflow(257, poolsize-initpoolptr); //pool size
	if (poolptr-strstart[strptr] < 256)
	{
		dvibuf[dviptr++] = xxx1;
		if (dviptr == dvilimit)
			dviswap();
		dvibuf[dviptr++] = poolptr-strstart[strptr];
		if (dviptr == dvilimit)
			dviswap();
	}
	else
	{
		dvibuf[dviptr++] = xxx4;
		if (dviptr == dvilimit)
			dviswap();
		dvifour(poolptr-strstart[strptr]);
	}
	for (auto k = strstart[strptr]; k <poolptr; k++)
	{
		dvibuf[dviptr++] = strpool[k];
		if (dviptr == dvilimit)
			dviswap();
	}
	poolptr = strstart[strptr];
}
