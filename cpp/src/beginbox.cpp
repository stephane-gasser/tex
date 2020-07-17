#include "beginbox.h"
#include "lecture.h"
#include "noeud.h"
#include "erreur.h"
#include "impression.h"
#include "vsplit.h"
#include "lecture.h"
#include "normalparagraph.h"
#include "pushnest.h"
#include "boxend.h"
#include "texte.h"

static halfword& every_hbox(void) { return equiv(every_hbox_loc); }

//! Now that we can see what eventually happens to boxes, we can consider
//! the first steps in their creation. The \a begin_box routine is called when
//! \a box_context is a context specification, \a cur_chr specifies the type of
//! box desired, and <em> cur_cmd=make_box </em>.
void beginbox(int boxcontext, eightbits cmd, halfword chr, halfword align)
{
	halfword p, q; // run through the current list
	quarterword m; // the length of a replacement list
	halfword k; // 0 or vmode or hmode
	eightbits n; // a box number
	int val;
	switch (chr)
	{
		case box_code:
			val = scaneightbitint(align);
			curbox = box(val);
			box(val) = 0; // the box becomes void, at the same level
			break;
		case copy_code:
			curbox = copynodelist(box(scaneightbitint(align)));
			break;
		case last_box_code:
			// If the current list ends with a box node, delete it from 
			// the list and make |cur_box| point to it; otherwise set |cur_box:=null|
			curbox = 0;
			if (abs(mode) == mmode)
				error("You can't use `"+cmdchr(cmd, chr)+"' in "+asMode(mode), "Sorry; this \\lastbox will be void.", align);
			else 
				if (mode == vmode && head == tail)
					error("You can't use `"+cmdchr(cmd, chr)+"' in "+asMode(mode), "Sorry...I usually can't take things from the current page.\nThis \\lastbox will therefore be void.", align);
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
			n = scaneightbitint(align);
			if (!scankeyword("to", align))
				error("Missing `to' inserted", "I'm working on `\\vsplit<box number> to <dimen>';\nwill look for the <dimen> next.", align);
			curbox = vsplit(n, scan_normal_dimen(align));
			break;
		default:
			k = chr-4;
			saved(0) = boxcontext;
			if (k == hmode)
				if (boxcontext < box_flag && abs(mode) == vmode)
					std::tie(cmd, chr, std::ignore) = scanspec(adjusted_hbox_group, true, align);
				else
					std::tie(cmd, chr, std::ignore) = scanspec(hbox_group, true, align);
			else
			{
				if (k == vmode)
					std::tie(cmd, chr, std::ignore) = scanspec(vbox_group, true, align);
				else
				{
					std::tie(cmd, chr, std::ignore) = scanspec(vtop_group, true, align);
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
	boxend(boxcontext, align); //in simple cases, we use the box immediately
}
