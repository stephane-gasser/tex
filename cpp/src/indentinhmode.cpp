#include "indentinhmode.h"
#include "noeud.h"

void indentinhmode(void)
{
	if (curchr > 0)
	{
		auto p = newnullbox();
		width(p) = par_indent();
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
