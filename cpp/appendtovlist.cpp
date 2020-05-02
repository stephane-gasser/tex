#include "appendtovlist.h"
#include "newparamglue.h"
#include "newskipparam.h"

void appendtovlist(halfword b)
{
	if (prev_depth > ignore_depth)
	{
		scaled d = mem[baseline_skip()+1].int_-prev_depth-mem[b+3].int_;
		halfword p;
		if (d < dimen_par(line_skip_limit_code))
			p = newparamglue(0);
		else
		{
			p = newskipparam(1);
			mem[tempptr+1].int_ = d;
		}
		tail_append(p);
	}
	tail_append(b);
	prev_depth = mem[b+2].int_;
}
