#include "setmathchar.h"
#include "xtoken.h"
#include "newnoad.h"
#include "backinput.h"

void setmathchar(int c)
{
	if (c >= 0x80'00)
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
		subtype(p+1) = c%0x1'00;
		type(p+1) = (c/0x1'00)%6;
		if (c >= 0x70'00)
		{
			if (int_par(cur_fam_code) >= 0 && int_par(cur_fam_code) < 0x10)
				type(p+1) = int_par(cur_fam_code);
			type(p) = 0x10;
		}
		else
			type(p) = 0x10+c/0x10'00;
		tail_append(p);
	}
}
