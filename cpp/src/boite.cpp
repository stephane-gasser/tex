#include "boite.h"
#include "noeud.h"
#include "alignement.h"
#include "police.h"
#include "formule.h"
#include "calcul.h"
#include "lecture.h"
#include "buildpage.h"
#include "equivalent.h"
#include "impression.h"
#include "shipout.h"
#include "erreur.h"
#include "vsplit.h"
#include "normalparagraph.h"
#include "pushnest.h"
#include "erreur.h"
#include "badness.h"
#include "sauvegarde.h"
#include "popnest.h"
#include "fichier.h"

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
			scaled v = fonts[P->font].char_width(P->character);
			if (v != b->width)
				p->link = new KernNode(b->width-v);
		}
		delete b;
		auto g = new GlueNode(ss_glue);
		g->link = p;
		followUntilBeforeTarget(p);
		p->link = new GlueNode(ss_glue);
		return hpack(g, w, exactly);
	}
	b->width = w;
	return b;
}

BoxNode *cleanbox(NoadContent &P, smallnumber s)
{
	LinkedNode *q; //beginning of a list to be boxed
	do
	{
		switch (P.math_type)
		{
			case math_char:
			{
				curmlist = new Noad;
				dynamic_cast<Noad*>(curmlist)->nucleus = P;
				break;
			}
			case sub_box:
				q = P.info;
				continue;
				break;
			case sub_mlist: 
				curmlist = P.info;
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
	} while (false);
	BoxNode *x;
	if (q == nullptr || q->is_char_node() || q->link || q->type > vlist_node || dynamic_cast<BoxNode*>(q)->shift_amount)
			x = hpack(q, 0, additional);
		else
			x = dynamic_cast<BoxNode*>(q);
	q = x->list_ptr;
	if (q->is_char_node())
	{
		auto r = q->link;
		if (r && r->link == nullptr && !r->is_char_node() && r->type == kern_node)
		{
			delete r;
			q->link = nullptr;
		}
	}
	return x;
}

void alterboxdimen(halfword c)
{
	auto b = box(scaneightbitint());
	scanoptionalequals();
	if (b == nullptr)
		return;
	switch (c)
	{
		case width_offset:
			b->width = scan_normal_dimen();
			break;
		case height_offset:
			b->height = scan_normal_dimen();
			break;
		case depth_offset:
			b->depth = scan_normal_dimen();
	}
}

void boxend(int boxcontext)
{
	if (boxcontext < box_flag)
	{
		if (curbox)
		{
			curbox->shift_amount = boxcontext;
			if (abs(mode) == vmode)
			{
				appendtovlist(curbox);
				if (adjusttail)
				{
					if (adjust_head != adjusttail)
						tail_append(adjust_head);
					adjusttail = nullptr;
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
					auto p = new Noad; //\a ord_noad for new box in math mode
					p->nucleus.math_type = sub_box;
					p->nucleus.info = curbox;
					curbox = dynamic_cast<BoxNode*>(p);
				}
				tail_append(curbox);
			}
		}
	}
	else 
		if (boxcontext < ship_out_flag) // Store (c) \a cur_box in a box register
			if (boxcontext < box_flag+256)
				eqdefine_(&eqtb_local[boxcontext-box_flag+box_base-local_base], box_ref, curbox);
			else
				geqdefine_(&eqtb_local[boxcontext-box_flag-256+box_base-local_base], box_ref, curbox);
		else 
			if (curbox && boxcontext > ship_out_flag) // Append a new leader node that uses \a cur_box
			{
				auto t = getXTokenSkipSpaceAndEscape();
				if ((t.cmd == hskip && abs(mode) != vmode) || (t.cmd == vskip && abs(mode) == vmode))
				{
					appendglue(t.chr);
					auto Tail = dynamic_cast<GlueNode*>(tail);
					Tail->subtype = boxcontext-(leader_flag-a_leaders);
					Tail->leader_ptr = curbox;
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

//! Now that we can see what eventually happens to boxes, we can consider
//! the first steps in their creation. The \a begin_box routine is called when
//! \a box_context is a context specification, \a cur_chr specifies the type of
//! box desired, and <em> cur_cmd=make_box </em>.
void beginbox(int boxcontext, Token t)
{
	switch (t.chr)
	{
		case box_code:
		{
			int val = scaneightbitint();
			curbox = box(val);
			setBox(val, nullptr); // the box becomes void, at the same level
			break;
		}
		case copy_code:
			curbox = dynamic_cast<BoxNode*>(copynodelist(box(scaneightbitint())));
			break;
		case last_box_code:
			// If the current list ends with a box node, delete it from 
			// the list and make |cur_box| point to it; otherwise set |cur_box:=null|
			curbox = nullptr;
			switch (mode)
			{
				case mmode:
				case -mmode:
					error("You can't use `"+cmdchr(t)+"' in "+asMode(mode), "Sorry; this \\lastbox will be void.");
					break;
				case vmode:
					if (head == tail)
					{
						error("You can't use `"+cmdchr(t)+"' in "+asMode(mode), "Sorry...I usually can't take things from the current page.\nThis \\lastbox will therefore be void.");
						break;
					}
					[[fallthrough]];
				default:
					if (!tail->is_char_node() && tail->type <= vlist_node)
						for (auto p = head; true; next(p)) // run through the current list
						{
							if (!p->is_char_node() && p->type == disc_node)
							{
								auto rep = dynamic_cast<DiscNode*>(p)->replace_count;
								for (int m = 0; m < rep; m++)
									next(p);
								if (p == tail)
									break;
							}
							if (p->link == tail)
							{
								curbox = dynamic_cast<BoxNode*>(tail);
								curbox->shift_amount = 0;
								tail = p;
								tail->link = nullptr;
								break;
							}
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
			switch (k)
			{
				case hmode:
					if (boxcontext < box_flag && abs(mode) == vmode)
						t = scanspec(adjusted_hbox_group, boxcontext);
					else
						t = scanspec(hbox_group, boxcontext);
					break;
				case vmode:
					t = scanspec(vbox_group, boxcontext);
					normalparagraph();
					break; 
				default:
					t = scanspec(vtop_group, boxcontext);
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

BoxNode* charbox(internalfontnumber f, quarterword c)
{
	auto b = new BoxNode;
	auto &ft = fonts[f];
	b->width = ft.char_width(c)+ft.char_italic(c);
	b->height = ft.char_height(c);
	b->depth = ft.char_depth(c);
	b->list_ptr = new CharNode(f, c);
	return b;
}

void ensurevbox(eightbits n)
{
	auto p = box(n);
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

static glueord getOrder(scaled *total)
{
	glueord o;
	if (total[3])
		o = 3;
	else 
		if (total[2])
			o = 2;
		else 
			if (total[1])
				o = 1;
			else
				o = 0;
	return o;
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
	while (p)
	{
		if (p->is_char_node())
			confusion("vpack");
		else
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				{
					auto P = dynamic_cast<BoxNode*>(p);
					x += d+P->height;
					d = P->depth;
					w = std::max(P->width+P->shift_amount, w);
					break;
				}
				case rule_node:
				case unset_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					x += d+P->height;
					d = P->depth;
					w = std::max(P->width, w);
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
					totalstretch[g->stretch_order] += g->stretch;
					totalshrink[g->shrink_order] += g->shrink;
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
		next(p);
	}
	r->width = w;
	r->depth = std::min(l, d);
	if (d > l)
		x += d-l;
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
			auto o = getOrder(totalstretch);
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
			auto o = getOrder(totalshrink);
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
	fontinshortdisplay = null_font;
	print(shortdisplay(r->list_ptr)+"\n");
	diagnostic(showbox(r)+"\n");
}

BoxNode* hpack(LinkedNode *p, scaled w, smallnumber m)
{
	lastbadness = 0;
	auto r = new BoxNode;
	r->type = hlist_node;
	r->subtype = 0;
	r->shift_amount = 0;
	r->list_ptr = p;
	auto q = r->list_ptr;
	scaled h = 0;
	scaled d = 0;
	scaled x = 0;
	std::fill(totalstretch, totalstretch+4, 0);
	std::fill(totalshrink, totalshrink+4, 0);
	while (p)
	{
		for (;p->is_char_node(); next(p))
		{
			auto P = dynamic_cast<CharNode*>(p);
			auto &ft = fonts[P->font];
			x += ft.char_width(P->character);
			h = std::max(ft.char_height(P->character), h);
			d = std::max(ft.char_depth(P->character), d);
		}
		if (p)
		{
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				{
					auto P = dynamic_cast<BoxNode*>(p);
					x += P->width;
					scaled s = P->shift_amount;
					h = std::max(P->height-s, h);
					d = std::max(P->depth+s, d);
					break;
				}
				case rule_node:
				case unset_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					x += P->width;
					h = std::max(P->height, h);
					d = std::max(P->depth, d);
					break;
				}
				case ins_node:
				case mark_node:
					if (adjusttail)
					{
						followUntilBeforeTarget(q, p);
						adjusttail->link = p;
						adjusttail = p;
						next(p);
						q->link = p;
						p = q;
					}
					break;
				case adjust_node: 
					if (adjusttail)
					{
						followUntilBeforeTarget(q, p);
						adjusttail->link = dynamic_cast<AdjustNode*>(p)->adjust_ptr;
						followUntilBeforeTarget(adjusttail);
						next(p);
						delete q->link;
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
					totalstretch[g->stretch_order] += g->stretch;
					totalshrink[g->shrink_order] += g->shrink;
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
					x += dynamic_cast<MathNode*>(p)->width;
					break;
				case ligature_node:
				{
					auto P = dynamic_cast<LigatureNode*>(p);
					lig_trick->font = P->lig_char.font;
					lig_trick->character = P->lig_char.character;
					lig_trick->link = p->link;
					p = lig_trick;
					continue;
				}
			}
			next(p);
		}
	}
	if (adjusttail)
		adjusttail->link = nullptr;
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
			auto o = getOrder(totalstretch);
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
			auto o = getOrder(totalshrink);
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
						followUntilBeforeTarget(q);
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

void package(smallnumber c, Token t)
{
	unsave();
	auto s2 = savestack.back()->int_;
	savestack.pop_back();
	auto s1 = savestack.back()->int_;
	savestack.pop_back();
	auto s0 = savestack.back()->int_;
	savestack.pop_back();
	if (mode == -hmode)
		curbox = hpack(head->link, s2, s1);
	else
	{
		curbox = vpackage(head->link, s2, s1, box_max_depth());
		if (c == vtop_code)
		{
			scaled h = 0;
			auto p = dynamic_cast<RuleNode*>(curbox->list_ptr);
			if (p && p->type <= rule_node)
				h = p->height;
			curbox->height = h;
			curbox->depth += curbox->height-h;
		}
	}
	popnest();
	boxend(s0);
}

void unpackage(halfword c)
{
	int val = scaneightbitint();
	auto p = box(val);
	if (p == nullptr)
		return;
	if (abs(mode) == mmode || (abs(mode) == vmode && p->type != vlist_node) || (abs(mode) == hmode && p->type != hlist_node))
	{
		error("Incompatible list can't be unboxed", "Sorry, Pandora. (You sneaky devil.)\nI refuse to unbox an \\hbox in vertical mode or vice versa.\nAnd I can't open any boxes in math mode.");
		return;
	}
	if (c == copy_code)
		tail->link = copynodelist(p->list_ptr);
	else
	{
		tail->link = p->list_ptr;
		setBox(val, nullptr);
		delete p;
	}
	followUntilBeforeTarget(tail);
}
