#include "indentinhmode.h"
#include "newnullbox.h"
#include "newnoad.h"

void indentinhmode(void)
{
	if (curchr > 0)
	{
		auto p = newnullbox();
		mem[p+1].int_ = dimen_par(par_indent_code);
		if (abs(mode) == 102)
			space_factor = 1000;
		else
		{
			auto q = newnoad();
			link(q+1) = 2;
			info(q+1) = p;
			p = q;
		}
		tail_append(p);
	}
}
