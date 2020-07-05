#include "beginbox.h"
#include "scaneightbitint.h"
#include "copynodelist.h"
#include "youcant.h"
#include "erreur.h"
#include "scankeyword.h"
#include "impression.h"
#include "vsplit.h"
#include "scandimen.h"
#include "normalparagraph.h"
#include "scanspec.h"
#include "pushnest.h"
#include "begintokenlist.h"
#include "boxend.h"
#include "texte.h"

static halfword& every_hbox(void) { return equiv(every_hbox_loc); }

static void erreurBeginbox1(void)
{
	youcant();
	helpptr = 1;
	helpline[0] = "Sorry; this \\lastbox will be void.";
	error();
}

static void erreurBeginbox2(void)
{
	youcant();
	helpptr = 2;
	helpline[1] = "Sorry...I usually can't take things from the current page.";
	helpline[0] = "This \\lastbox will therefore be void.";
	error();
}

static void erreurBeginbox3(void)
{
	print_err("Missing `to' inserted");
	helpptr = 2;
	helpline[1] = "I'm working on `\\vsplit<box number> to <dimen>';";
	helpline[0] = "will look for the <dimen> next.";
	error();
}

//! Now that we can see what eventually happens to boxes, we can consider
//! the first steps in their creation. The \a begin_box routine is called when
//! \a box_context is a context specification, \a cur_chr specifies the type of
//! box desired, and <em> cur_cmd=make_box </em>.
void beginbox(int boxcontext)
{
	halfword p, q; // run through the current list
	quarterword m; // the length of a replacement list
	halfword k; // 0 or vmode or hmode
	eightbits n; // a box number
	switch (curchr)
	{
		case box_code:
			scaneightbitint();
			curbox = box(curval);
			box(curval) = 0; // the box becomes void, at the same level
			break;
		case copy_code:
			scaneightbitint();
			curbox = copynodelist(box(curval));
			break;
		case last_box_code:
			// If the current list ends with a box node, delete it from 
			// the list and make |cur_box| point to it; otherwise set |cur_box:=null|
			curbox = 0;
			if (abs(mode) == mmode)
				erreurBeginbox1();
			else 
				if (mode == vmode && head == tail)
					erreurBeginbox2();
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
		case vsplit_code:
			scaneightbitint();
			n = curval;
			if (!scankeyword("to"))
				erreurBeginbox3();
			scan_normal_dimen();
			curbox = vsplit(n, curval);
			break;
		default:
			k = curchr-4;
			savestack[saveptr].int_ = boxcontext;
			if (k == hmode)
				if (boxcontext < 0x40'00'00'00 && abs(mode) == vmode)
					scanspec(3, true);
				else
					scanspec(2, true);
			else
			{
				if (k == vmode)
					scanspec(4,	true);
				else
				{
					scanspec(5, true);
					k = vmode;
				}
				normalparagraph();
			}
			pushnest();
			mode = -k;
			if (k == vmode)
			{
				prev_depth = ignore_depth;
				if (every_vbox())
					begintokenlist(every_vbox(), every_vbox_text);
			}
			else
			{
				space_factor = 1000;
				if (every_hbox())
					begintokenlist(every_hbox(), every_hbox_text);
			}
			return;
	}
	boxend(boxcontext); //in simple cases, we use the box immediately
}
