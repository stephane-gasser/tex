#include "hpack.h"
#include "impression.h"
#include "badness.h"
#include "noeud.h"

static int hbadness(void) { return int_par(hbadness_code); }
static int hfuzz(void) { return dimen_par(hfuzz_code); }

static void goto50(halfword r)
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
	print(shortdisplay(list_ptr(r))+"\n");
	diagnostic(showbox(r)+"\n");
}

halfword hpack(halfword p, scaled w, smallnumber m)
{
	lastbadness = 0;
	auto r = getnode(box_node_size);
	type(r) = 0;
	subtype(r) = 0;
	glue_shrink(r) = 0;
	auto q = r+5;
	list_ptr(r) = p;
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
		while (is_char_node(p))
		{
			f = type(p);
			auto i = char_info(f, character(p));
			x += char_width(f, i);
			s = char_height(f, i);
			if (s > h)
				h = s;
			s = char_depth(f, i);
			if (s > d)
				d = s;
			p = link(p);
		}
		if (p)
		{
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case rule_node:
				case unset_node:
					x += width(p);
					if (type(p) >= rule_node)
						s = 0;
					else
						s = shift_amount(p);
					if (height(p)-s > h)
						h = height(p)-s;
					if (depth(p) > d)
						d = depth(p)+s;
					break;
				case ins_node:
				case mark_node:
				case adjust_node: 
					if (adjusttail)
					{
						while (link(q) != p)
							q = link(q);
						if (type(p) == adjust_node)
						{
							link(adjusttail) = adjust_ptr(p);
							while (link(adjusttail))
								adjusttail = link(adjusttail);
							p = link(p);
							freenode(link(q), 2);
						}
						else
						{
							link(adjusttail) = p;
							adjusttail = p;
							p = link(p);
						}
						link(q) = p;
						p = q;
					}
					break;
				case whatsit_node:
					break;
				case glue_node:
					g = info(p+1);
					x += width(g);
					o = type(g);
					totalstretch[o] += stretch(g);
					o = subtype(g);
					totalshrink[o] += shrink(g);
					if (subtype(p) >= 100)
					{
						g = link(p+1);
						if (shrink(g) > h)
							h = shrink(g);
						if (stretch(g) > d)
							d = stretch(g);
					}
					break;
				case kern_node:
				case math_node: 
					x += width(p);
					break;
				case ligature_node:
					mem[lig_trick] = mem[lig_char(p)];
					link(lig_trick) = link(p);
					p = lig_trick;
					continue;
			}
			p = link(p);
		}
	}
	if (adjusttail)
		link(adjusttail) = 0;
	height(r) = h;
	depth(r) = d;
	if (m == additional)
		w += x;
	width(r) = w;
	x = w-x;
	if (x == 0)
	{
		glue_sign(r) = normal;
		glue_order(r) = 0;
		glue_set(r) = 0.0;
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
			glue_order(r) = o;
			glue_sign(r) = stretching;
			if (totalstretch[o])
				glue_set(r) = x/totalstretch[o];
			else
			{
				glue_sign(r) = normal;
				glue_set(r) = 0.0;
			}
			if (o == 0 && list_ptr(r))
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
			glue_order(r) = o;
			glue_sign(r) = shrinking;
			if (totalshrink[o])
				glue_set(r) = (-x)/totalshrink[o];
			else
			{
				glue_sign(r) = normal;
				glue_set(r) = 0.0;
			}
			if (totalshrink[o] < -x && o == 0 && list_ptr(r))
			{
				lastbadness = 1000000;
				glue_set(r) = 1.0;
				if (-x-totalshrink[0] > hfuzz() || hbadness() < 100)
				{
					if (overfull_rule() > 0 && -x-totalshrink[0] > hfuzz())
					{
						while (link(q))
							q = link(q);
						link(q) = newrule();
						width(link(q)) = overfull_rule();
					}
					print("\nOverfull \\hbox ("+asScaled(-x-totalshrink[0])+"pt too wide");
					goto50(r);
				}
			}
			else 
				if (o == 0)
					if (list_ptr(r))
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
