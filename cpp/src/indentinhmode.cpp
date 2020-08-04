#include "indentinhmode.h"
#include "noeud.h"

void indentinhmode(Token t)
{
	if (t.chr > 0)
	{
		auto p = new BoxNode;
		p->width = par_indent();
		if (abs(mode) == hmode)
			space_factor = 1000;
		else
		{
			auto q = newnoad();
			math_type(nucleus(q)) = sub_box;
			info(nucleus(q)) = p->num;
			p->num = q;
		}
		tail_append(p);
	}
}
