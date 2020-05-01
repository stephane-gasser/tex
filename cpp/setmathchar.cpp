#include "setmathchar.h"
#include "xtoken.h"
#include "newnoad.h"
#include "backinput.h"

void setmathchar(int c)
{
	if (c >= 32768)
	{
		curcs = curchr+1;
		curcmd = eq_type(curcs);
		curchr = equiv(curcs);
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
			if (int_par(cur_fam_code) >= 0 && int_par(cur_fam_code) < 16)
				type(p+1) = int_par(cur_fam_code);
			type(p) = 16;
		}
		else
			type(p) = 16+c/4096;
		link(curlist.tailfield) = p;
		curlist.tailfield = p;
	}
}
