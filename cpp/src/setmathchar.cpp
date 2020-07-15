#include "setmathchar.h"
#include "lecture.h"
#include "noeud.h"
#include "backinput.h"

void setmathchar(int c, halfword chr)
{
	if (c >= 0x80'00)
	{
		halfword cs = chr+active_base;
		eightbits cmd = eq_type(cs);
		halfword chr = equiv(cs);
		halfword tok;
		std::tie(cmd, chr, tok) = xtoken(cmd, chr, cs);
		backinput(tok);
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
