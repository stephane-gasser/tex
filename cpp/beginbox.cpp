#include "beginbox.h"
#include "scaneightbitint.h"
#include "copynodelist.h"
#include "youcant.h"
#include "error.h"
#include "scankeyword.h"
#include "printnl.h"
#include "print.h"
#include "vsplit.h"
#include "scandimen.h"
#include "normalparagraph.h"
#include "scanspec.h"
#include "pushnest.h"
#include "begintokenlist.h"
#include "boxend.h"

void beginbox(int boxcontext)
{
	halfword p, q;
	quarterword m;
	halfword k;
	eightbits n;
	switch (curchr)
	{
		case 0:
			scaneightbitint();
			curbox = box(curval);
			box(curval) = 0;
			break;
		case 1:
			scaneightbitint();
			curbox = copynodelist(box(curval));
			break;
		case 2:
			curbox = 0;
			if (abs(mode) == mmode)
			{
				youcant();
				helpptr = 1;
				helpline[0] = 1069; //Sorry; this \lastbox will be void.
				error();
			}
			else 
				if (mode == vmode && head == tail)
				{
					youcant();
					helpptr = 2;
					helpline[1] = 1070; //Sorry...I usually can't take things from the current page.
					helpline[0] = 1071; //This \lastbox will therefore be void.
					error();
				}
				else 
					if (tail < himemmin)
						if (type(tail) == hlist_node || type(tail) == vlist_node)
						{
							q = head;
							bool brk = false;
							do
							{
								p = q;
								if (q < himemmin && type(q) == disc_node) // 7
								{
									for (m = 1 ; m <= subtype(q); m++)
										p = link(p);
									if (p == tail)
									{
										brk = true;
										break;
									}
								}
								q = link(p);
							} while (q != tail);
							if (!brk)
							{
								curbox = tail;
								shift_amount(curbox) = 0;
								tail = p;
								link(p) = 0;
							}
						}
			break;
		case 3:
			scaneightbitint();
			n = curval;
			if (!scankeyword(841)) //to
			{
				printnl(262); //! 
				print(1072); //Missing `to' inserted
				helpptr = 2;
				helpline[1] = 1073; //I'm working on `\vsplit<box number> to <dimen>';
				helpline[0] = 1074; //will look for the <dimen> next.
				error();
			}
			scandimen(false, false, false);
			curbox = vsplit(n, curval);
			break;
		default:
			k = curchr-4;
			savestack[saveptr].int_ = boxcontext;
			if (k == 102)
				if (boxcontext < 0x40'00'00'00 && abs(mode) == vmode)
					scanspec(3, true);
				else
					scanspec(2, true);
			else
			{
				if (k == 1)
					scanspec(4,	true);
				else
				{
					scanspec(5, true);
					k = 1;
				}
				normalparagraph();
			}
			pushnest();
			mode = -k;
			if (k == 1)
			{
				prev_depth = ignore_depth;
				if (every_vbox())
					begintokenlist(every_vbox(), 11);
			}
			else
			{
				space_factor = 1000;
				if (every_hbox())
					begintokenlist(every_hbox(), 10);
			}
			return;
	}
	boxend(boxcontext);
}
