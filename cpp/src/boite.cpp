#include "boite.h"
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
#include "erreur.h"
#include "badness.h"

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
	if (box[b] == nullptr)
		return;
	switch (c)
	{
		case width_offset:
			box[b]->width = scan_normal_dimen();
			break;
		case height_offset:
			box[b]->height = scan_normal_dimen();
			break;
		case depth_offset:
			box[b]->depth = scan_normal_dimen();
	}
}

void boxend(int boxcontext)
{
	halfword p; //\a ord_noad for new box in math mode
	if (boxcontext < box_flag)
	{
		if (curbox)
		{
			curbox->shift_amount = boxcontext;
			if (abs(mode) == vmode)
			{
				appendtovlist(curbox->num);
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
					info(nucleus(p)) = curbox->num;
					curbox->num = p;
				}
				tail_append(curbox);
			}
		}
	}
	else 
		if (boxcontext < ship_out_flag) // Store (c) \a cur_box in a box register
			if (boxcontext < box_flag+256)
				eqdefine(boxcontext-box_flag+box_base, box_ref, curbox->num);
			else
				geqdefine(boxcontext-box_flag-256+box_base, box_ref, curbox->num);
		else 
			if (curbox && boxcontext > ship_out_flag) // Append a new leader node that uses \a cur_box
			{
				auto t = getXTokenSkipSpaceAndEscape();
				if ((t.cmd == hskip && abs(mode) != vmode) || (t.cmd == vskip && abs(mode) == vmode))
				{
					appendglue(t.chr);
					subtype(tail->num) = boxcontext-(leader_flag-a_leaders);
					dynamic_cast<GlueNode*>(tail)->leader_ptr = curbox;
				}
				else
				{
					backerror(t, "Leaders not followed by proper glue", "You should say `\\leaders <box or rule><hskip or vskip>'.\nI found the <box or rule>, but there's no suitable\n<hskip or vskip>, so I'm ignoring these leaders.");
					flushnodelist(curbox);
				}
			}

	else
	shipout(curbox->num);
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
	switch (t.chr)
	{
		case box_code:
		{
			int val = scaneightbitint();
			curbox = box[val];
			box[val] = nullptr; // the box becomes void, at the same level
			break;
		}
		case copy_code:
			curbox = dynamic_cast<BoxNode*>(copynodelist(box[scaneightbitint()]));
			break;
		case last_box_code:
			// If the current list ends with a box node, delete it from 
			// the list and make |cur_box| point to it; otherwise set |cur_box:=null|
			curbox = nullptr;
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
								curbox = dynamic_cast<BoxNode*>(tail);
								curbox->shift_amount = 0;
								tail = p;
								p->link = nullptr;
							}
						}
			break;
		case vsplit_code:
		{
			auto n = scaneightbitint();	 // a box number
			if (!scankeyword("to"))
				error("Missing `to' inserted", "I'm working on `\\vsplit<box number> to <dimen>';\nwill look for the <dimen> next.");
			curbox = vsplit(n, scan_normal_dimen());
			break;
		}
		default:
		{
			halfword k = t.chr-4; // 0 or vmode or hmode
			saved(0) = boxcontext;
			switch (k)
			{
				case hmode:
					if (boxcontext < box_flag && abs(mode) == vmode)
						t = scanspec(adjusted_hbox_group, true);
					else
						t = scanspec(hbox_group, true);
					break;
				case vmode:
					t = scanspec(vbox_group, true);
					normalparagraph();
					break;
				default:
					t = scanspec(vtop_group, true);
					k = vmode;
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
	auto p = box[n];
	if (p && p->type == hlist_node)
		boxerror(n, "Insertions can only be added to a vbox", "Tut tut: You're trying to \\insert into a\n\\box register that now contains an \\hbox.\nProceed, and I'll discard its present contents.");
}

static void goto50v(BoxNode *r)
{
	if (outputactive)
		print(") has occurred while \\output is active");
	else
	{
		if (packbeginline)
			print(") in alignment at lines "+std::to_string(abs(packbeginline))+"--");
		else
			print(") detected at line ");
		print(std::to_string(line)+"\n");
	}
	diagnostic(showbox(r)+"\n");
}

//! special case of unconstrained depth
BoxNode *vpack(LinkedNode *p, scaled h, smallnumber m)
{
	return vpackage(p, h, m, max_dimen);
}

BoxNode *vpackage(LinkedNode *p, scaled h, smallnumber m, scaled l)
{
	lastbadness = 0;
	auto r = new BoxNode;
	r->type = vlist_node;
	r->subtype = 0;
	r->shift_amount = 0;
	r->list_ptr = p;
	scaled w = 0;
	scaled d = 0;
	scaled x = 0;
	totalstretch[0] = 0;
	totalshrink[0] = 0;
	totalstretch[1] = 0;
	totalshrink[1] = 0;
	totalstretch[2] = 0;
	totalshrink[2] = 0;
	totalstretch[3] = 0;
	totalshrink[3] = 0;
	scaled s;
	glueord o;
	while (p)
	{
		if (p->is_char_node())
			confusion("vpack");
		else
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				case rule_node:
				case unset_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					x += d+P->height;
					d = P->depth;
					if (p->type >= rule_node) // rule_node ou unset_node
						s = 0;
					else
						s = dynamic_cast<BoxNode*>(p)->shift_amount;
					if (P->width+s > w)
						w = P->width+s;
					break;
				}
				case whatsit_node:
					break;
				case glue_node:
				{
					auto P = dynamic_cast<GlueNode*>(p);
					x += d;
					d = 0;
					auto g = P->glue_ptr;
					x += g->width;
					o = g->stretch_order;
					totalstretch[o] += g->stretch;
					o = g->shrink_order;
					totalshrink[o] += g->shrink;
					if (P->subtype >= a_leaders && g->width > w)
						w = g->width;
					break;
				}
				case kern_node:
				{
					x += d+dynamic_cast<KernNode*>(p)->width;
					d = 0;
				}
			}
		p = p->link;
	}
	r->width = w;
	if (d > l)
	{
		x += d-l;
		r->depth = l;
	}
	else
		r->depth = d;
	if (m == additional)
		h += x;
	r->height = h;
	x = h-x;
	if (x == 0)
	{
		r->glue_sign = normal;
		r->glue_order = 0;
		r->glue_set = 0.0;
	}
	else 
		if (x > 0)
		{
			glueord o;
			if (totalstretch[3])
				o = 3;
			else 
				if (totalstretch[2])
					o = 2;
				else 
					if (totalstretch[1])
						o = 1;
					else 
						o = 0;
			r->glue_order = o;
			r->glue_sign = stretching;
			if (totalstretch[o])
				r->glue_set = x/totalstretch[o];
			else
			{
				r->glue_sign = normal;
				r->glue_set = 0.0;
			}
			if (o == 0)
			if (r->list_ptr)
			{
				lastbadness = badness(x, totalstretch[0]);
				if (lastbadness > vbadness())
				{
					print("\n"+std::string(lastbadness > 100 ? "Underfull": "Loose")+"\\vbox (badness "+std::to_string(lastbadness));
					goto50v(r);
				}
			}
		}
		else
		{
			glueord o;
			if (totalshrink[3])
				o = 3;
			else 
				if (totalshrink[2])
					o = 2;
				else 
					if (totalshrink[1])
						o = 1;
					else
						o = 0;
			r->glue_order = o;
			r->glue_sign = shrinking;
			if (totalshrink[o])
				r->glue_set = (-x)/totalshrink[o];
			else
			{
				r->glue_sign = normal;
				r->glue_set = 0.0;
			}
			if (totalshrink[o] < -x && o == 0 && r->list_ptr)
			{
				lastbadness = 1000000;
				r->glue_set = 1.0;
				if (-x-totalshrink[0] > vfuzz() || vbadness() < 100)
				{
					print("\nOverfull \\vbox ("+asScaled(-x-totalshrink[0])+"pt too high");
					goto50v(r);
				}
			}
			else 
				if (o == 0 && r->list_ptr)
				{
					lastbadness = badness(-x, totalshrink[0]);
					if (lastbadness > vbadness())
					{
						print("\nTight \\vbox (badness "+std::to_string(lastbadness));
						goto50v(r);
					}
				}
		}
	return r;
}

static int hbadness(void) { return int_par(hbadness_code); }
static int hfuzz(void) { return dimen_par(hfuzz_code); }

static void goto50h(BoxNode *r)
{
	if (outputactive)
		print(") has occurred while \\output is active");
	else
		if (packbeginline)
			print(") in "+std::string(packbeginline > 0 ? "paragraph" : "alignment")+" at lines "+std::to_string(abs(packbeginline))+"--"+std::to_string(line));
		else
			print(") detected at line"+std::to_string(line));
	println();
	fontinshortdisplay = fonts[null_font];
	print(shortdisplay(r->list_ptr->num)+"\n");
	diagnostic(showbox(r)+"\n");
}

BoxNode* hpack(LinkedNode *p, scaled w, smallnumber m)
{
	lastbadness = 0;
	auto r = new BoxNode;
	r->type = hlist_node;
	r->subtype = 0;
	r->shift_amount = 0;
	auto q = r->list_ptr;
	r->list_ptr = p;
	scaled h = 0;
	scaled d = 0;
	scaled x = 0;
	totalstretch[0] = 0;
	totalshrink[0] = 0;
	totalstretch[1] = 0;
	totalshrink[1] = 0;
	totalstretch[2] = 0;
	totalshrink[2] = 0;
	totalstretch[3] = 0;
	totalshrink[3] = 0;
	while (p)
	{
		scaled s;
		glueord o;
		while (p->is_char_node())
		{
			auto P = dynamic_cast<CharNode*>(p);
			auto ft = P->font;
			x += ft.char_width(P->character);
			s = ft.char_height(P->character);
			if (s > h)
				h = s;
			s = ft.char_depth(P->character);
			if (s > d)
				d = s;
			p = p->link;
		}
		if (p)
		{
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				case rule_node:
				case unset_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					x += P->width;
					if (p->type >= rule_node)
						s = 0;
					else
						s = dynamic_cast<BoxNode*>(p)->shift_amount;
					if (P->height-s > h)
						h = P->height-s;
					if (P->depth > d)
						d = P->depth+s;
					break;
				}
				case ins_node:
				case mark_node:
				case adjust_node: 
					if (adjusttail)
					{
						while (q->link != p)
							q = q->link;
						if (p->type == adjust_node)
						{
							link(adjusttail) = adjust_ptr(p->num);
							while (link(adjusttail))
								adjusttail = link(adjusttail);
							p = p->link;
							delete q->link;
						}
						else
						{
							link(adjusttail) = p->num;
							adjusttail = p->num;
							p = p->link;
						}
						q->link = p;
						p = q;
					}
					break;
				case whatsit_node:
					break;
				case glue_node:
				{
					auto P = dynamic_cast<GlueNode*>(p);
					auto g = P->glue_ptr;
					x += g->width;
					o = g->stretch_order;
					totalstretch[o] += g->stretch;
					o = g->shrink_order;
					totalshrink[o] += g->shrink;
					if (P->subtype >= 100)
					{
						auto g = dynamic_cast<RuleNode*>(P->leader_ptr);
						if (g->height > h)
							h = g->height;
						if (g->depth > d)
							d = g->depth;
					}
					break;
				}
				case kern_node:
					x += dynamic_cast<KernNode*>(p)->width;
					break;
				case math_node: 
					x += width(p->num);
					break;
				case ligature_node:
					mem[lig_trick->num] = mem[lig_char(p->num)];
					lig_trick->link = p->link;
					p = lig_trick;
					continue;
			}
			p = p->link;
		}
	}
	if (adjusttail)
		link(adjusttail) = 0;
	r->height = h;
	r->depth = d;
	if (m == additional)
		w += x;
	r->width = w;
	x = w-x;
	if (x == 0)
	{
		r->glue_sign = normal;
		r->glue_order = 0;
		r->glue_set = 0.0;
	}
	else 
		if (x > 0)
		{
			glueord o;
			if (totalstretch[3])
				o = 3;
			else 
				if (totalstretch[2])
					o = 2;
				else 
					if (totalstretch[1])
						o = 1;
					else
						o = 0;
			r->glue_order = o;
			r->glue_sign = stretching;
			if (totalstretch[o])
				r->glue_set = x/totalstretch[o];
			else
			{
				r->glue_sign = normal;
				r->glue_set = 0.0;
			}
			if (o == 0 && r->list_ptr)
			{
				lastbadness = badness(x, totalstretch[0]);
				if (lastbadness > hbadness())
				{
					println();
					printnl(std::string(lastbadness > 100 ? "Underfull" : "Loose")+" \\hbox (badness "+std::to_string(lastbadness));
					goto50h(r);
				}
			}
		}
		else
		{
			glueord o;
			if (totalshrink[3])
				o = 3;
			else 
				if (totalshrink[2])
					o = 2;
				else 
					if (totalshrink[1])
						o = 1;
					else
						o = 0;
			r->glue_order = o;
			r->glue_sign = shrinking;
			if (totalshrink[o])
				r->glue_set = (-x)/totalshrink[o];
			else
			{
				r->glue_sign = normal;
				r->glue_set = 0.0;
			}
			if (totalshrink[o] < -x && o == 0 && r->list_ptr)
			{
				lastbadness = 1000000;
				r->glue_set = 1.0;
				if (-x-totalshrink[0] > hfuzz() || hbadness() < 100)
				{
					if (overfull_rule() > 0 && -x-totalshrink[0] > hfuzz())
					{
						while (q->link)
							q = q->link;
						auto R = new RuleNode;
						R->width = overfull_rule();
						q->link = R;
					}
					print("\nOverfull \\hbox ("+asScaled(-x-totalshrink[0])+"pt too wide");
					goto50h(r);
				}
			}
			else 
				if (o == 0)
					if (r->list_ptr)
					{
						lastbadness = badness(-x, totalshrink[0]);
						if (lastbadness > hbadness())
						{
							print("\nTight \\hbox (badness "+std::to_string(lastbadness));
							goto50h(r);
						}
					}
		}
	return r;
}
