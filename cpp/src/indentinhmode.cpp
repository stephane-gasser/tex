#include "indentinhmode.h"
#include "equivalent.h"
#include "noeud.h"
#include "etat.h"

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
			auto q = new Noad;
			q->nucleus.math_type = sub_box;
			q->nucleus.info = p;
			p = dynamic_cast<BoxNode*>(q);
		}
		tail_append(p);
	}
}
