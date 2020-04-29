#include "appendtovlist.h"
#include "newparamglue.h"
#include "newskipparam.h"

void appendtovlist(halfword b)
{
	if (curlist.auxfield.int_ > -65536000)
	{
		scaled d = mem[eqtb[2883].hh.rh+1].int_-curlist.auxfield.int_-mem[b+3].int_;
		halfword p;
		if (d < eqtb[5832].int_)
			p = newparamglue(0);
		else
		{
			p = newskipparam(1);
			mem[tempptr+1].int_ = d;
		}
		link(curlist.tailfield) = p;
		curlist.tailfield = p;
	}
	link(curlist.tailfield) = b;
	curlist.tailfield = b;
	curlist.auxfield.int_ = mem[b+2].int_;
}
