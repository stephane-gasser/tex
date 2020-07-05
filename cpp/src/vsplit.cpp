#include "vsplit.h"
#include "impression.h"
#include "erreur.h"
#include "vertbreak.h"
#include "deletetokenref.h"
#include "prunepagetop.h"
#include "freenode.h"
#include "vpackage.h"
#include "texte.h"

static void erreurVsplit(void)
{
	print_err(esc("vsplit")+" needs a "+esc("vbox"));
	helpptr = 2;
	helpline[1] = "The box you are trying to split is an \\hbox.";
	helpline[0] = "I can't split such a box, so I'll leave it alone.";
	error();
}

halfword vsplit(eightbits n, scaled h)
{
	auto v = box(n);
	if (split_first_mark)
	{
		deletetokenref(split_first_mark);
		split_first_mark = 0;
		deletetokenref(split_bot_mark);
		split_bot_mark = 0;
	}
	if (v == 0)
		return 0;
	if (type(v) != 1)
	{
		erreurVsplit();
		return 0;
	}
	auto q = vertbreak(list_ptr(v), h, split_max_depth());
	auto p = list_ptr(v);
	if (p == q)
		list_ptr(v) = 0;
	else
		while (true)
		{
			if (type(p) == mark_node) //4
				if (split_first_mark == 0)
				{
					split_first_mark = mark_ptr(p);
					split_bot_mark = split_first_mark;
					info(split_first_mark) += 2;
				}
				else
				{
					deletetokenref(split_bot_mark);
					split_bot_mark = mark_ptr(p);
					info(split_bot_mark)++;
				}
			if (link(p) == q)
			{
				link(p) = 0;
				break;
			}
			p = link(p);
		}
	q = prunepagetop(q);
	p = list_ptr(v);
	freenode(v, box_node_size);
	box(n) = q == 0 ? 0 : vpack(q, 0, additional);
	return vpackage(p, h, exactly, split_max_depth());
}
