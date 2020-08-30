#include "setmathchar.h"
#include "lecture.h"
#include "noeud.h"
#include "backinput.h"
#include "equivalent.h"

void setmathchar(int c, Token t)
{
	if (c >= 0x80'00)
	{
		t.cs = t.chr+active_base;
		t.cmd = eqtb_active[t.chr].type;
		t.chr = eqtb_active[t.chr].int_;
		t = xtoken(t);
		backinput(t);
	}
	else
	{
		auto p = new Noad;
		p->nucleus.math_type = math_char;
		p->nucleus.character = c%(1<<8);
		p->nucleus.fam = (c>>8)%(1<<4);
		if (c >= var_code)
		{
			if (fam_in_range())
				p->nucleus.fam = cur_fam();
			p->type = ord_noad;
		}
		else
			p->type = ord_noad+(c>>12);
		tail_append(p);
	}
}
