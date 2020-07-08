#include "appendtovlist.h"
#include "noeud.h"

static halfword& baseline_skip(void) { return glue_par(baseline_skip_code); }
static int line_skip_limit(void) { return dimen_par(line_skip_limit_code); }

//! When a box is being appended to the current vertical list, the
//! baselineskip calculation is handled by the \a append_to_vlist routine.
void appendtovlist(halfword b)
{
	if (prev_depth > ignore_depth)
	{
		scaled d = width(baseline_skip())-prev_depth-height(b);
		halfword p;
		if (d < line_skip_limit())
			p = newparamglue(line_skip_code);
		else
		{
			p = newskipparam(baseline_skip_code);
			width(tempptr) = d;
		}
		tail_append(p);
	}
	tail_append(b);
	prev_depth = depth(b);
}
