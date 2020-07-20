#include "setmathchar.h"
#include "lecture.h"
#include "noeud.h"
#include "backinput.h"

void setmathchar(int c, Token t)
{
	if (c >= 0x80'00)
	{
		t.cs = t.chr+active_base;
		t.cmd = eq_type(t.cs);
		t.chr = equiv(t.cs);
		t = xtoken(t);
		backinput(t);
	}
	else
	{
		auto p = newnoad();
		math_type(nucleus(p)) = math_char;
		character(nucleus(p)) = c%(1<<8);
		fam(nucleus(p)) = (c>>8)%(1<<4);
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
