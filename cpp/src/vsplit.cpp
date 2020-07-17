#include "vsplit.h"
#include "impression.h"
#include "erreur.h"
#include "vertbreak.h"
#include "lecture.h"
#include "prunepagetop.h"
#include "noeud.h"
#include "vpackage.h"
#include "texte.h"

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
	if (type(v) != vlist_node)
	{
		error(esc("vsplit")+" needs a "+esc("vbox"), "The box you are trying to split is an \\hbox.\nI can't split such a box, so I'll leave it alone.", curalign);
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
