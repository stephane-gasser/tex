#include "hlistout.h"
#include "dviswap.h"
#include "movement.h"
#include "prunemovements.h"
#include "dvifontdef.h"
#include "dvifour.h"
#include "vlistout.h"
#include "dvipop.h"
#include "outwhat.h"
#include "confusion.h"
#include <cmath>

void vlistout(void)
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
	auto leftedge = curh;
	curv -= height(thisbox);
	auto topedge = curv;
	while (p)
	{
		if (p >= himemmin)
			confusion("vlistout");
		else
		{
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
					if (list_ptr(p) == 0)
						curv += height(p)+depth(p);
					else
					{
						curv += height(p);
						if (curv != dviv)
						{
							movement(curv-dviv, 157);
							dviv = curv;
						}
						auto saveh = dvih;
						auto savev = dviv;
						curh = leftedge+shift_amount(p);
						tempptr = p;
						if (type(p) == 1)
							vlistout();
						else
							hlistout();
						dvih = saveh;
						dviv = savev;
						curv = savev+depth(p);
						curh = leftedge;
					}
					break;
				case rule_node:
					ruleht = height(p);
					ruledp = depth(p);
					rulewd = width(p);
					if (is_running(rulewd))
						rulewd = width(thisbox);
					ruleht += ruledp;
					curv += ruleht;
					if (ruleht > 0 &&rulewd > 0)
					{
						synch_h();
						synch_v();
						dvi_out(put_rule);
						dvifour(ruleht);
						dvifour(rulewd);
					}
					p = link(p);
					continue;
				case whatsit_node:
					outwhat(p);
					break;
				case glue_node:
					g = glue_ptr(p);
					ruleht = width(g)-curg;
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
					ruleht += curg;
					if (subtype(p) >= 100)
					{
						halfword leaderbox = link(p+1);
						if (type(leaderbox) == 2)
						{
							rulewd = width(leaderbox);
							ruledp = 0;
							if (is_running(rulewd))
								rulewd = width(thisbox);
							ruleht += ruledp;
							curv += ruleht;
							if (ruleht > 0 &&rulewd > 0)
							{
								synch_h();
								synch_v();
								dvi_out(put_rule);
								dvifour(ruleht);
								dvifour(rulewd);
							}
							p = link(p);
							continue;
						}
						auto leaderht = height(leaderbox)+depth(leaderbox);
						if ((leaderht > 0) and (ruleht > 0))
						{
							ruleht += 10;
							auto edge = curv+ruleht;
							scaled lx = 0;
							if (subtype(p) == 100)
							{
								auto savev = curv;
								curv = topedge+leaderht*((curv-topedge)/leaderht);
								if (curv < savev)
									curv = curv+leaderht;
							}
							else
							{
								lq = ruleht/leaderht;
								lr = ruleht%leaderht;
								if (subtype(p) == 101)
									curv += lr/2;
								else
								{
									lx = lr/(lq+1);
									curv += (lr-(lq-1)*lx)/2;
								}
							}
							while (curv+leaderht <= edge)
							{
								curh = leftedge+shift_amount(leaderbox);
								synch_h();
								auto saveh = dvih;
								curv += height(leaderbox);
								synch_v();
								auto savev = dviv;
								tempptr = leaderbox;
								bool outerdoingleaders = doingleaders;
								doingleaders = true;
								if (type(leaderbox) == 1)
									vlistout();
								else
									hlistout();
								doingleaders = outerdoingleaders;
								dviv = savev;
								dvih = saveh;
								curh = leftedge;
								curv = savev-height(leaderbox)+leaderht+lx;
							}
							curv = edge-10;
							p = link(p);
							continue;
						}
					}
					curv = curv+ruleht;
					p = link(p);
					continue;
				case kern_node: 
					curv += width(p);
				}
			p = link(p);
			continue;
		}
	}
	prunemovements(saveloc);
	if (curs > 0)
		dvipop(saveloc);
	curs--;
}
