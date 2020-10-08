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
#include "etat.h"
#include "erreur.h"
#include "badness.h"
#include "sauvegarde.h"
#include "fichier.h"

BoxNode* rebox(BoxNode *b, scaled w)
{
	if (b->width != w && b->list_ptr)
	{
		if (b->type == vlist_node)
			b = hpack(b, 0, additional);
		auto p = b->list_ptr;
		if (p->type == char_node && p->link == nullptr)
		{
			scaled v = p->getWidth();
			if (v != b->width)
				p->link = new KernNode(b->width-v);
		}
		delete b;
		auto g = new GlueNode(ss_glue);
		g->link = p; // g -> b->list_ptr = p
		followUntilEnd(b->list_ptr, p); // g -> b->list_ptr -> ... -> p -> 0
		p->link = new GlueNode(ss_glue); // g -> b->list_ptr -> ... -> p -> GlueNode
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
				curmlist->nucleus = P;
				break;
			}
			case sub_box:
				q = P.info;
				continue;
				break;
			case sub_mlist: 
				curmlist = dynamic_cast<Noad*>(P.info);
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
		setCurSize(curstyle);
	} while (false);
	BoxNode *x;
	if (q == nullptr || q->type == char_node || q->link || q->type > vlist_node || dynamic_cast<BoxNode*>(q)->shift_amount)
			x = hpack(q, 0, additional);
		else
			x = dynamic_cast<BoxNode*>(q);
	q = x->list_ptr;
	if (q->type == char_node)
	{
		auto r = q->link;
		if (r && r->link == nullptr && r->type == kern_node)
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

void boxend(int boxcontext, RuleNode* curbox)
{
	if (boxcontext < box_flag) //<Append box |cur_box| to the current list, shifted by |box_context|
	{
		if (curbox)
		{
			curbox->setShift(boxcontext);
			if (abs(mode) == vmode)
			{
				appendtovlist(dynamic_cast<BoxNode*>(curbox));
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
		{
			if (boxcontext < box_flag+256)
				eqtb_local[boxcontext-box_flag+box_base-local_base].define(noPrefix, box_ref, curbox);
			else
				eqtb_local[boxcontext-box_flag-256+box_base-local_base].define(globalPrefix, box_ref, curbox);
		}
		else 
			if (curbox)
				if (boxcontext > ship_out_flag) // Append a new leader node that uses \a cur_box
				{
					auto t = getXTokenSkipSpaceAndEscape();
					if ((t.cmd == hskip && abs(mode) != vmode) || (t.cmd == vskip && abs(mode) == vmode))
					{
						auto g = glueToAppend(t.chr);
						g->subtype = boxcontext-(leader_flag-a_leaders);
						g->leader_ptr = curbox;
						tail_append(g);
					}
					else
					{
						backerror(t, "Leaders not followed by proper glue", "You should say `\\leaders <box or rule><hskip or vskip>'.\nI found the <box or rule>, but there's no suitable\n<hskip or vskip>, so I'm ignoring these leaders.");
						flushnodelist(curbox);
					}
				}
				else
					shipout(dynamic_cast<BoxNode*>(curbox));
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
			auto b = box(val);
			setBox(val, nullptr); // the box becomes void, at the same level
			boxend(boxcontext, b); //in simple cases, we use the box immediately
			break;
		}
		case copy_code:
			boxend(boxcontext, dynamic_cast<BoxNode*>(copynodelist(box(scaneightbitint())))); //in simple cases, we use the box immediately
			break;
		case last_box_code:
		{
			// If the current list ends with a box node, delete it from 
			// the list and make |cur_box| point to it; otherwise set |cur_box:=null|
			BoxNode *b = nullptr;
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
					if (tail->type <= vlist_node)
						for (auto p = head; true; next(p)) // run through the current list
						{
							if (p->type == disc_node)
							{
								auto rep = dynamic_cast<DiscNode*>(p)->replace_count;
								for (int m = 0; m < rep; m++)
									next(p);
								if (p == tail)
									break;
							}
							if (p->link == tail)
							{
								b = dynamic_cast<BoxNode*>(tail);
								b->setShift(0);
								tail = p;
								tail->link = nullptr;
								break;
							}
						}
			}
			boxend(boxcontext, b); //in simple cases, we use the box immediately
			break;
		}
		case vsplit_code:
		{
			auto n = scaneightbitint();	 // a box number
			if (!scankeyword("to"))
				error("Missing `to' inserted", "I'm working on `\\vsplit<box number> to <dimen>';\nwill look for the <dimen> next.");
			boxend(boxcontext, vsplit(n, scan_normal_dimen())); //in simple cases, we use the box immediately
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
					beginTokenListAboveMacro(every_vbox(), every_vbox_text);
			}
			else
			{
				space_factor = 1000;
				if (every_hbox())
					beginTokenListAboveMacro(every_hbox(), every_hbox_text);
			}
			return;
		}
	}
}

BoxNode* charbox(internalfontnumber f, quarterword c)
{
	auto b = new BoxNode;
	auto cn = new CharNode(f, c);
	b->width = cn->width()+cn->italic();
	b->height = cn->height();
	b->depth = cn->depth();
	b->list_ptr = cn;
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
	for (; p; next(p))
		switch (p->type)
		{
			case char_node:
				confusion("vpack");
				break;
			case hlist_node:
			case vlist_node:
			{
				x += d+p->getHeight();
				d = p->getDepth();
				w = std::max(p->getWidth()+dynamic_cast<BoxNode*>(p)->shift_amount, w);
				break;
			}
			case rule_node:
			case unset_node:
			{
				x += d+p->getHeight();
				d = p->getDepth();
				w = std::max(p->getWidth(), w);
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
				x += d+p->getWidth();
				d = 0;
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
	r->list_ptr = p;
	scaled h = 0;
	scaled d = 0;
	scaled x = 0;
	std::fill_n(totalstretch, 4, 0);
	std::fill_n(totalshrink, 4, 0);
	scaled s = 0;
	while (p)
	{
		switch (p->type)
		{
			case hlist_node:
			case vlist_node:
				s = dynamic_cast<BoxNode*>(p)->shift_amount; [[fallthrough]];
			case char_node:
			case rule_node:
			case unset_node:
				h = std::max(p->getHeight()-s, h);
				d = std::max(p->getDepth()+s, d); [[fallthrough]];
			case kern_node:
			case math_node: 
				x += p->getWidth();
				break;
			case ins_node:
			case mark_node:
				if (adjusttail)
				{
					LinkedNode *q;
					followUntilBeforeTarget(r->list_ptr, q, p); // r->list_ptr -> ... -> q -> p
					appendAtEnd(adjusttail, p);
					next(p);
					q->link = p;
					p = q;
				}
				break;
			case adjust_node: 
				if (adjusttail)
				{
					followUntilEnd(dynamic_cast<AdjustNode*>(p)->adjust_ptr, adjusttail); // p->adjust_ptr -> ... -> adjusttail -> 0
					LinkedNode *q;
					followUntilBeforeTarget(r->list_ptr, q, p); // r->list_ptr -> ... -> q -> p
					next(p); //r->list_ptr -> ... -> q -> p' -> p=p'->link
					delete q->link; 
					q->link = p; //r->list_ptr -> ... -> q -> p=p'
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
					h = std::max(g->height, h);
					d = std::max(g->depth, d);
				}
				break;
			}
			case ligature_node:
			{
				auto P = dynamic_cast<LigatureNode*>(p);
				lig_trick->font = P->font;
				lig_trick->character = P->character;
				lig_trick->link = p->link;
				p = lig_trick;
				continue;
			}
		}
		next(p);
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
					print(std::string(lastbadness > 100 ? "Underfull" : "Loose")+" \\hbox (badness "+std::to_string(lastbadness));
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
						LinkedNode *q;
						followUntilEnd(r->list_ptr, q);
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
	BoxNode *b;
	if (mode == -hmode)
		b = hpack(head->link, s2, s1);
	else
	{
		auto box = vpackage(head->link, s2, s1, box_max_depth());
		if (c == vtop_code)
		{
			scaled h = 0;
			if (box->list_ptr && box->list_ptr->type <= rule_node)
				h = box->list_ptr->getHeight();
			box->height = h;
			box->depth += box->height-h;
		}
		b = box;
	}
	popnest();
	boxend(s0, b);
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
		followUntilEnd(copynodelist(p->list_ptr), tail);
	else
	{
		followUntilEnd(p->list_ptr, tail);
		setBox(val, nullptr);
		delete p;
	}
}
