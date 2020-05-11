#include "indentinhmode.h"
#include "newnullbox.h"
#include "newnoad.h"

void indentinhmode(void)
{
	if (curchr > 0)
	{
		auto p = newnullbox();
		width(p) = dimen_par(par_indent_code);
		if (abs(mode) == hmode)
			space_factor = 1000;
		else
		{
			auto q = newnoad();
			math_type(nucleus(q)) = sub_box;
			info(nucleus(q)) = p;
			p = q;
		}
		tail_append(p);
	}
}
