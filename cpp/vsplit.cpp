#include "vsplit.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"
#include "vertbreak.h"
#include "deletetokenref.h"
#include "prunepagetop.h"
#include "freenode.h"
#include "vpackage.h"
#include "texte.h"

halfword vsplit(eightbits n, scaled h)
{
	auto v = box(n);
	if (curmark[3])
	{
		deletetokenref(curmark[3]);
		curmark[3] = 0;
		deletetokenref(curmark[4]);
		curmark[4] = 0;
	}
	if (v == 0)
		return 0;
	if (type(v) != 1)
	{
		printnl("! ");
		print("");
		printesc("vsplit");
		print(" needs a ");
		printesc("vbox");
		helpptr = 2;
		helpline[1] = "The box you are trying to split is an \\hbox.";
		helpline[0] = "I can't split such a box, so I'll leave it alone.";
		error();
		return 0;
	}
	auto q = vertbreak(link(v+5), h, dimen_par(split_max_depth_code));
	auto p = link(v+5);
	if (p == q)
		link(v+5) = 0;
	else
		while (true)
		{
			if (type(p) == mark_node) //4
				if (curmark[3] == 0)
				{
					curmark[3] = mark_ptr(p);
					curmark[4] = curmark[3];
					info(curmark[3]) += 2;
				}
				else
				{
					deletetokenref(curmark[4]);
					curmark[4] = mark_ptr(p);
					info(curmark[4])++;
				}
			if (link(p) == q)
			{
				link(p) = 0;
				break;
			}
			p = link(p);
		}
	q = prunepagetop(q);
	p = link(v+5);
	freenode(v, 7);
	if (q == 0)
		box(n) = 0;
	else
		box(n) = vpackage(q, 0, 1, max_dimen);
	return vpackage(p, h, 0, dimen_par(split_max_depth_code));
}
