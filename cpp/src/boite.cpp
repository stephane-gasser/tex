#include "boite.h"
#include "hpack.h"
#include "noeud.h"
#include "police.h"
#include "mlisttohlist.h"
#include "xovern.h"
#include "lecture.h"
#include "buildpage.h"
#include "eqdefine.h"
#include "geqdefine.h"
#include "impression.h"
#include "shipout.h"
#include "erreur.h"
#include "vsplit.h"
#include "normalparagraph.h"
#include "pushnest.h"


BoxNode* rebox(BoxNode *b, scaled w)
{
	if (b->width != w && b->list_ptr)
	{
		if (b->type == vlist_node)
			b = hpack(b, 0, additional);
		auto p = b->list_ptr;
		if (p->is_char_node() && p->link == nullptr)
		{
			auto P = dynamic_cast<CharNode*>(p);
			scaled v = P->font.char_width(P->character);
			if (v != b->width)
				p->link = new KernNode(b->width-v);
		}
		delete b;
		auto g = new GlueNode(ss_glue);
		g->link = p;
		while (p->link)
			p = p->link;
		p->link = new GlueNode(ss_glue);
		return hpack(g, w, exactly);
	}
	b->width = w;
	return b;
}

BoxNode *cleanbox(halfword p, smallnumber s)
{
	LinkedNode *q;
	do
	{
		switch (link(p))
		{
			case 1:
				curmlist = newnoad();
				mem[nucleus(curmlist)] = mem[p];
				break;
			case 2:
				q->num = info(p);
				continue;
				break;
			case 3: 
				curmlist = info(p);
				break;
			default:
				q = new BoxNode;
				continue;
		}
		auto savestyle = curstyle;
		curstyle = s;
		mlistpenalties = false;
		mlisttohlist();
		q = temp_head->link;
		curstyle = savestyle;
		if (curstyle < 4)
			cursize = 0;
		else
			cursize = 16*((curstyle-2)/2);
		curmu = xovern(math_quad(cursize), 18);
		break;
	} while (false);
	BoxNode *x;
	if (q->is_char_node() || q == nullptr)
		x = hpack(q, 0, additional);
	else 
		if (q->link == nullptr && q->type <= vlist_node && dynamic_cast<BoxNode*>(q)->shift_amount == 0)
			x = dynamic_cast<BoxNode*>(q);
		else
			x = hpack(q, 0, additional);
	q = x->list_ptr;
	if (q->is_char_node())
	{
		auto r = q->link;
		if (r && r->link == nullptr && !r->is_char_node() && r->type == kern_node)
		{
			delete r;
			q->link = 0;
		}
	}
	return x;
}

void alterboxdimen(Token t)
{
	auto c = t.chr;
	auto b = scaneightbitint();
	scanoptionalequals();
	int val = scan_normal_dimen();
	if (box(b))
		mem[box(b)+c].int_ = val;
}

void boxend(int boxcontext)
{
	halfword p; //\a ord_noad for new box in math mode
	if (boxcontext < box_flag)
	{
		if (curbox)
		{
			shift_amount(curbox) = boxcontext;
			if (abs(mode) == vmode)
			{
				appendtovlist(curbox);
				if (adjusttail)
				{
					if (adjust_head->num != adjusttail)
						tail_append(adjust_head);
					adjusttail = 0;
				}
				if (mode > 0)
					buildpage();
			}
			else
			{
				if (abs(mode) == hmode)
					space_factor = 1000;
				else
				{
					p = newnoad();
					math_type(nucleus(p)) = sub_box;
					info(nucleus(p)) = curbox;
					curbox = p;
				}
				tail_append(curbox);
			}
		}
	}
	else 
		if (boxcontext < ship_out_flag) // Store (c) \a cur_box in a box register
			if (boxcontext < box_flag+256)
				eqdefine(boxcontext-box_flag+box_base, box_ref, curbox);
			else
				geqdefine(boxcontext-box_flag-256+box_base, box_ref, curbox);
		else 
			if (curbox && boxcontext > ship_out_flag) // Append a new leader node that uses \a cur_box
			{
				auto t = getXTokenSkipSpaceAndEscape();
				if ((t.cmd == hskip && abs(mode) != vmode) || (t.cmd == vskip && abs(mode) == vmode))
				{
					appendglue(t.chr);
					subtype(tail->num) = boxcontext-(leader_flag-a_leaders);
					leader_ptr(tail->num) = curbox;
				}
				else
				{
					backerror(t, "Leaders not followed by proper glue", "You should say `\\leaders <box or rule><hskip or vskip>'.\nI found the <box or rule>, but there's no suitable\n<hskip or vskip>, so I'm ignoring these leaders.");
					flushnodelist(curbox);
				}
			}

	else
	shipout(curbox);
}

static halfword& every_hbox(void) { return equiv(every_hbox_loc); }

//! Now that we can see what eventually happens to boxes, we can consider
//! the first steps in their creation. The \a begin_box routine is called when
//! \a box_context is a context specification, \a cur_chr specifies the type of
//! box desired, and <em> cur_cmd=make_box </em>.
void beginbox(int boxcontext, Token t)
{
	LinkedNode *p, *q; // run through the current list
	quarterword m; // the length of a replacement list
	halfword k; // 0 or vmode or hmode
	eightbits n; // a box number
	int val;
	switch (t.chr)
	{
		case box_code:
			val = scaneightbitint();
			curbox = box(val);
			box(val) = 0; // the box becomes void, at the same level
			break;
		case copy_code:
			curbox = copynodelist(box(scaneightbitint()));
			break;
		case last_box_code:
			// If the current list ends with a box node, delete it from 
			// the list and make |cur_box| point to it; otherwise set |cur_box:=null|
			curbox = 0;
			if (abs(mode) == mmode)
				error("You can't use `"+cmdchr(t)+"' in "+asMode(mode), "Sorry; this \\lastbox will be void.");
			else 
				if (mode == vmode && head == tail)
					error("You can't use `"+cmdchr(t)+"' in "+asMode(mode), "Sorry...I usually can't take things from the current page.\nThis \\lastbox will therefore be void.");
				else 
					if (!tail->is_char_node())
						if (tail->type == hlist_node || tail->type == vlist_node)
						{
							q = head;
							bool brk = false;
							do
							{
								p = q;
								if (!q->is_char_node() && q->type == disc_node) // 7
								{
									for (m = 1 ; m <= subtype(q->num); m++)
										p = p->link;
									if (p == tail)
									{
										brk = true;
										break;
									}
								}
								q = p->link;
							} while (q != tail);
							if (!brk)
							{
								curbox = tail->num;
								shift_amount(curbox) = 0;
								tail = p;
								p->link = nullptr;
							}
						}
			break;
		case vsplit_code:
			n = scaneightbitint();
			if (!scankeyword("to"))
				error("Missing `to' inserted", "I'm working on `\\vsplit<box number> to <dimen>';\nwill look for the <dimen> next.");
			curbox = vsplit(n, scan_normal_dimen());
			break;
		default:
			k = t.chr-4;
			saved(0) = boxcontext;
			if (k == hmode)
				if (boxcontext < box_flag && abs(mode) == vmode)
					t = scanspec(adjusted_hbox_group, true);
				else
					t = scanspec(hbox_group, true);
			else
			{
				if (k == vmode)
					t = scanspec(vbox_group, true);
				else
				{
					t = scanspec(vtop_group, true);
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

BoxNode* charbox(const Font &ft, quarterword c)
{
	auto b = new BoxNode;
	b->width = ft.char_width(c)+ft.char_italic(c);
	b->height = ft.char_height(c);
	b->depth = ft.char_depth(c);
	b->list_ptr = new CharNode(ft, c);
	return b;
}

void ensurevbox(eightbits n)
{
	auto p = box(n);
	if (p && type(p) == hlist_node)
		boxerror(n, "Insertions can only be added to a vbox", "Tut tut: You're trying to \\insert into a\n\\box register that now contains an \\hbox.\nProceed, and I'll discard its present contents.");
}

