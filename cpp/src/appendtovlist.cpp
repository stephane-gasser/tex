#include "appendtovlist.h"
#include "newparamglue.h"
#include "newskipparam.h"

static halfword& baseline_skip(void) { return glue_par(baseline_skip_code); }
static int line_skip_limit(void) { return dimen_par(line_skip_limit_code); }

void appendtovlist(halfword b)
{
	if (prev_depth > ignore_depth)
	{
		scaled d = width(baseline_skip())-prev_depth-height(b);
		halfword p;
		if (d < line_skip_limit())
			p = newparamglue(0);
		else
		{
			p = newskipparam(1);
			width(tempptr) = d;
		}
		tail_append(p);
	}
	tail_append(b);
	prev_depth = depth(b);
}
