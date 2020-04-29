#include "setmathchar.h"
#include "xtoken.h"
#include "newnoad.h"
#include "backinput.h"

void setmathchar(int c)
{
	if (c >= 32768)
	{
		curcs = curchr+1;
		curcmd = eqtb[curcs].hh.b0;
		curchr = eqtb[curcs].hh.rh;
		xtoken();
		backinput();
	}
	else
	{
		auto p = newnoad();
		link(p+1) = 1;
		subtype(p+1) = c%256;
		type(p+1) = (c/256)%6;
		if (c >= 28672)
		{
			if (eqtb[5307].int_ >= 0 && eqtb[5307].int_ < 16)
				type(p+1) = eqtb[5307].int_;
			type(p) = 16;
		}
		else
			type(p) = 16+c/4096;
		link(curlist.tailfield) = p;
		curlist.tailfield = p;
	}
}
