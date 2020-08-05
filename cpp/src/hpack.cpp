#include "hpack.h"
#include "impression.h"
#include "badness.h"
#include "noeud.h"
#include "police.h"

static int hbadness(void) { return int_par(hbadness_code); }
static int hfuzz(void) { return dimen_par(hfuzz_code); }

static void goto50(BoxNode *r)
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
	diagnostic(showbox(r->num)+"\n");
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
					goto50(r);
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
					goto50(r);
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
							goto50(r);
						}
					}
		}
	return r;
}
