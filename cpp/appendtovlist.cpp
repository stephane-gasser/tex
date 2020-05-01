#include "appendtovlist.h"
#include "newparamglue.h"
#include "newskipparam.h"

void appendtovlist(halfword b)
{
	if (curlist.auxfield.int_ > -65536000)
	{
		scaled d = mem[baseline_skip()+1].int_-curlist.auxfield.int_-mem[b+3].int_;
		halfword p;
		if (d < dimen_par(line_skip_limit_code))
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
