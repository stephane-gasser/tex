#include "setmathchar.h"
#include "lecture.h"
#include "noeud.h"
#include "backinput.h"

void setmathchar(int c)
{
	if (c >= 0x80'00)
	{
		curcs = curchr+active_base;
		curcmd = eq_type(curcs);
		curchr = equiv(curcs);
		xtoken();
		backinput();
	}
	else
	{
		auto p = newnoad();
		math_type(nucleus(p)) = math_char;
		character(nucleus(p)) = c%0x1'00;
		fam(nucleus(p)) = (c>>8)%0x10;
		if (c >= var_code)
		{
			if (fam_in_range())
				fam(nucleus(p)) = cur_fam();
			type(p) = ord_noad;
		}
		else
			type(p) = ord_noad+(c>>12);
		tail_append(p);
	}
}
