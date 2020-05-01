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
	glueord gorder = subtype(thisbox+5);
	char gsign = type(thisbox+5);
	halfword p = link(thisbox+5);
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
	curv = curv-mem[thisbox+3].int_;
	auto topedge = curv;
	while (p)
	{
		if (p >= himemmin)
			confusion(827); //vlistout
		else
		{
			switch (type(p))
			{
				case 0:
				case 1:
					if (link(p+5) == 0)
						curv = curv+mem[p+3].int_+mem[p+2].int_;
					else
					{
						curv = curv+mem[p+3].int_;
						if (curv != dviv)
						{
							movement(curv-dviv, 157);
							dviv = curv;
						}
						auto saveh = dvih;
						auto savev = dviv;
						curh = leftedge+mem[p+4].int_;
						tempptr = p;
						if (type(p) == 1)
							vlistout();
						else
							hlistout();
						dvih = saveh;
						dviv = savev;
						curv = savev+mem[p+2].int_;
						curh = leftedge;
					}
					break;
				case 2:
					ruleht = mem[p+3].int_;
					ruledp = mem[p+2].int_;
					rulewd = mem[p+1].int_;
					if ((rulewd == -1073741824))
						rulewd = mem[thisbox+1].int_;
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
				case 8:
					outwhat(p);
					break;
				case 10:
					g = info(p+1);
					ruleht = mem[g+1].int_-curg;
					if (gsign != 0)
						if (gsign == 1)
						{
							if (type(g) == gorder)
							{
								curglue += mem[g+2].int_;
								float gluetemp = mem[thisbox+6].gr*curglue;
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
								curglue -= mem[g+3].int_;
								float gluetemp = mem[thisbox+6].gr*curglue;
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
							rulewd = mem[leaderbox+1].int_;
							ruledp = 0;
							if ((rulewd == -1073741824))
								rulewd = mem[thisbox+1].int_;
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
						auto leaderht = mem[leaderbox+3].int_+mem[leaderbox+2].int_;
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
								curh = leftedge+mem[leaderbox+4].int_;
								if (curh != dvih)
								{
									movement(curh-dvih, 143);
									dvih = curh;
								}
								auto saveh = dvih;
								curv = curv+mem[leaderbox+3].int_;
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
								curv = savev-mem[leaderbox+3].int_+leaderht+lx;
							}
							curv = edge-10;
							p = link(p);
							continue;
						}
					}
					curv = curv+ruleht;
					p = link(p);
					continue;
				case 11: 
					curv = curv+mem[p+1].int_;
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
