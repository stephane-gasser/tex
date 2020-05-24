#include "showactivities.h"
#include "printchar.h"
#include "printesc.h"
#include "printscaled.h"
#include "printtotals.h"
#include "printmode.h"
#include "println.h"
#include "print.h"
#include "printnl.h"
#include "printint.h"
#include "showbox.h"
#include "xovern.h"

void showactivities(void)
{
	nest[nestptr] = curlist;
	printnl("");
	println();
	for (int p = nestptr; p >= 0; p--)
	{
		int m = nest[p].modefield;
		memoryword a = nest[p].auxfield;
		printnl("### ");
		printmode(m);
		print(" entered at line ");
		printint(abs(nest[p].mlfield));
		if (m == hmode && nest[p].pgfield != 8585216)
		{
			print(" (language");
			printint(nest[p].pgfield%0x1'00'00);
			print(":hyphenmin");
			printint(nest[p].pgfield/4194304);
			printchar(',');
			printint((nest[p].pgfield/0x1'00'00)%64);
			printchar(')');
		}
		if (nest[p].mlfield < 0)
			print(" (\\output routine)");
		if (p == 0)
		{
			if (page_head != pagetail)
			{
				printnl("### current page:");
				if (outputactive)
					print(" (held over for link output)");
				showbox(link(page_head));
				if (pagecontents > 0)
				{
					printnl("total height ");
					printtotals();
					printnl(" goal height");
					printscaled(pagesofar[0]);
					halfword r = link(page_ins_head);
					while (r != page_ins_head)
					{
						println();
						printesc("insert");
						int t = subtype(r);
						printint(t);
						print(" adds ");
						if (count(t) == 1000)
							t = height(r);
						else
							t = xovern(height(r), 1000)*count(t);
						printscaled(t);
						if (type(r) == vlist_node)
						{
							halfword q = page_head;
							t = 0;
							do
							{
								q = link(q);
								if (type(q) == ins_node && subtype(q) == subtype(r))
									t++;
							} while (q != llink(r));
							print(", #");
							printint(t);
							print(" might split");
						}
						r = link(r);
					}
				}
			}
			;
			if (link(contrib_head))
			printnl("### recent contributions:");
		}
		showbox(link(nest[p].headfield));
		switch (abs(m)/101)
		{
			case 0:
				printnl("prevdepth ");
				if (a.int_ <= -0x1'00'00*1000)
					print("ignored");
				else
					printscaled(a.int_);
				if (nest[p].pgfield)
				{
					print(", prevgraf ");
					printint(nest[p].pgfield);
					print(" line");
					if (nest[p].pgfield != 1)
						printchar('s');
				}
				break;
			case 1:
				printnl("spacefactor ");
				printint(a.hh.lh);
				if (m > 0 && a.hh.rh > 0)
				{
					print(", current language ");
					printint(a.hh.rh);
				}
				break;
			case 2: 
				if (a.int_)
				{
					print("this will be denominator of:");
					showbox(a.int_);
				}
		}
	}
}
