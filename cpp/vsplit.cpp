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
		if (interaction == 3)
			printnl(262); //! 
		print(338); // 
		printesc(964); //vsplit
		print(965); // needs a 
		printesc(966); //vbox
		helpptr = 2;
		helpline[1] = 967; //The box you are trying to split is an \hbox.
		helpline[0] = 968; //I can't split such a box, so I'll leave it alone.
		error();
		return 0;
	}
	auto q = vertbreak(link(v+5), h, eqtb[5836].int_);
	auto p = link(v+5);
	if (p == q)
		link(v+5) = 0;
	else
		while (true)
		{
			if (type(p) == mark_node) //4
				if (curmark[3] == 0)
				{
					curmark[3] = mem[p+1].int_;
					curmark[4] = curmark[3];
					info(curmark[3]) += 2;
				}
				else
				{
					deletetokenref(curmark[4]);
					curmark[4] = mem[p+1].int_;
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
		box(n) = vpackage(q, 0, 1, 1073741823);
	return vpackage(p, h, 0, eqtb[5836].int_);
}
