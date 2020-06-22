#include "hlistout.h"
#include "dviswap.h"
#include "movement.h"
#include "prunemovements.h"
#include "dvifontdef.h"
#include "dvifour.h"
#include "vlistout.h"
#include "dvipop.h"
#include "outwhat.h"
#include <cmath>

void hlistout(void)
{
	scaled curg = 0;
	float curglue = 0.0;
	auto thisbox = tempptr;
	glueord gorder = glue_order(thisbox);
	char gsign = glue_sign(thisbox);
	halfword p = list_ptr(thisbox);
	curs++;
	if (curs > 0)
		dvi_out(push);
	if (curs > maxpush)
		maxpush = curs;
	int saveloc = dvioffset+dviptr;
	scaled baseline = curv;
	scaled leftedge = curh;
	while (p)
		if (is_char_node(p))
		{
			synch_h();
			synch_v();
			do
			{
				f = type(p);
				c = character(p);
				if (f != dvif)
				{
					if (!fontused[f])
					{
						dvifontdef(f);
						fontused[f] = true;
					}
					if (f <= 64+font_base)
						dvi_out(f-font_base-1+fnt_num_0);
					else
					{
						dvi_out(fnt1);
						dvi_out(f-font_base-1);
					}
					dvif = f;
				}
				;
				if (c >= 128)
					dvi_out(set1);
				dvi_out(c);
				curh += char_width(f, char_info(f, c));
				p = link(p);
			} while (is_char_node(p));
			dvih = curh;
		}
		else
		{
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
					if (list_ptr(p) == hlist_node)
						curh += width(p);
					else
					{
						auto saveh = dvih;
						auto savev = dviv;
						curv = baseline+shift_amount(p);
						tempptr = p;
						auto edge = curh;
						if (type(p) == vlist_node)
							vlistout();
						else
							hlistout();
						dvih = saveh;
						dviv = savev;
						curh = edge+width(p);
						curv = baseline;
					}
					break;
				case rule_node:
					ruleht = height(p);
					ruledp = depth(p);
					rulewd = width(p);
					if (is_running(ruleht))
						ruleht = height(thisbox);
					if (is_running(ruledp))
						ruledp = depth(thisbox);
					ruleht += ruledp;
					if (ruleht > 0 && rulewd > 0)
					{
						synch_h();
						curv = baseline+ruledp;
						synch_v();
						dvi_out(set_rule);
						dvifour(ruleht);
						dvifour(rulewd);
						curv = baseline;
						dvih = dvih+rulewd;
					}
					curh = curh+rulewd;
					p = link(p);
					continue;
				case whatsit_node:
					outwhat(p);
					break;
				case glue_node:
					g = info(p+1);
					rulewd = width(g)-curg;
					if (gsign)
						if (gsign == 1)
						{
							if (type(g) == gorder)
							{
								curglue += stretch(g);
								curg = round(vet_glue(glue_set(thisbox)*curglue));
							}
						}
						else 
							if (subtype(g) == gorder)
							{
								curglue -= shrink(g);
								curg = round(vet_glue(glue_set(thisbox)*curglue));
							}
					rulewd += curg;
					if (subtype(p) >= 100)
					{
						halfword leaderbox = link(p+1);
						if (type(leaderbox) == 2)
						{
							ruleht = height(leaderbox);
							ruledp = depth(leaderbox);
							if (is_running(ruleht))
								ruleht = height(thisbox);
							if (is_running(ruledp))
								ruledp = depth(thisbox);
							ruleht += ruledp;
							if (ruleht > 0 && rulewd > 0)
							{
								synch_h();
								curv = baseline+ruledp;
								synch_v();
								dvi_out(set_rule);
								dvifour(ruleht);
								dvifour(rulewd);
								curv = baseline;
								dvih = dvih+rulewd;
							}
							curh = curh+rulewd;
							p = link(p);
							continue;
						}
						scaled leaderwd = width(leaderbox);
						if (leaderwd > 0 && rulewd > 0)
						{
							rulewd = rulewd+10;
							auto edge = curh+rulewd;
							scaled lx = 0;
							if (subtype(p) == 100)
							{
								auto saveh = curh;
								curh = leftedge+leaderwd*((curh-leftedge)/leaderwd);
								if (curh < saveh)
									curh = curh+leaderwd;
							}
							else
							{
								lq = rulewd/leaderwd;
								lr = rulewd%leaderwd;
								if (subtype(p) == 101)
									curh += lr/2;
								else
								{
									lx = lr/(lq+1);
									curh += (lr-(lq-1)*lx)/2;
								}
							}
							while (curh+leaderwd <= edge)
							{
								curv = baseline+shift_amount(leaderbox);
								synch_v();
								auto savev = dviv;
								synch_h();
								auto saveh = dvih;
								tempptr = leaderbox;
								bool outerdoingleaders = doingleaders;
								doingleaders = true;
								if (type(leaderbox) == vlist_node)
									vlistout();
								else
									hlistout();
								doingleaders = outerdoingleaders;
								dviv = savev;
								dvih = saveh;
								curv = baseline;
								curh = saveh+leaderwd+lx;
							}
							curh = edge-10;
							p = link(p);
							continue;
						}
					}
					curh = curh+rulewd;
					p = link(p);
					continue;
				case kern_node:
				case math_node: 
					curh += width(p);
					break;
				case ligature_node:
					mem[lig_trick] = mem[lig_char(p)];
					link(lig_trick) = link(p);
					p = lig_trick;
					continue;
			}
			p = link(p);
			continue;
		}
	prunemovements(saveloc);
	if (curs > 0)
		dvipop(saveloc);
	curs--;
}

