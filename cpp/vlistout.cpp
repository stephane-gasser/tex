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
	{
		dvibuf[dviptr++] = push;
		if (dviptr == dvilimit)
			dviswap();
	}
	if (curs > maxpush)
		maxpush = curs;
	int saveloc = dvioffset+dviptr;
	auto leftedge = curh;
	curv -= height(thisbox);
	auto topedge = curv;
	while (p)
	{
		if (p >= himemmin)
			confusion(827); //vlistout
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
					if ((rulewd == null_flag))
						rulewd = width(thisbox);
					ruleht += ruledp;
					curv += ruleht;
					if (ruleht > 0 &&rulewd > 0)
					{
						if (curh != dvih)
						{
							movement(curh-dvih, 143);
							dvih = curh;
						}
						if (curv != dviv)
						{
							movement(curv-dviv, 157);
							dviv = curv;
						}
						dvibuf[dviptr++] = put_rule;
						if (dviptr == dvilimit)
							dviswap();
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
								float gluetemp = glue_set(thisbox)*curglue;
								if (gluetemp > 1000000000.0)
									gluetemp = 1000000000.0;
								else 
									if (gluetemp < -1000000000.0)
										gluetemp = -1000000000.0;
								curg = round(gluetemp);
							}
						}
						else 
							if (subtype(g) == gorder)
							{
								curglue -= shrink(g);
								float gluetemp = glue_set(thisbox)*curglue;
								if (gluetemp > 1000000000.0)
									gluetemp = 1000000000.0;
								else 
									if (gluetemp < -1000000000.0)
										gluetemp = -1000000000.0;
								curg = round(gluetemp);
							}
					ruleht += curg;
					if (subtype(p) >= 100)
					{
						halfword leaderbox = link(p+1);
						if (type(leaderbox) == 2)
						{
							rulewd = width(leaderbox);
							ruledp = 0;
							if ((rulewd == null_flag))
								rulewd = width(thisbox);
							ruleht += ruledp;
							curv += ruleht;
							if (ruleht > 0 &&rulewd > 0)
							{
								if (curh != dvih)
								{
									movement(curh-dvih, 143);
									dvih = curh;
								}
								if (curv != dviv)
								{
									movement(curv-dviv, 157);
									dviv = curv;
								}
								dvibuf[dviptr++] = put_rule;
								if (dviptr == dvilimit)
									dviswap();
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
								if (curh != dvih)
								{
									movement(curh-dvih, 143);
									dvih = curh;
								}
								auto saveh = dvih;
								curv += height(leaderbox);
								if (curv != dviv)
								{
									movement(curv-dviv, 157);
									dviv = curv;
								}
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
