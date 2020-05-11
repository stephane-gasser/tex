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
	{
		dvibuf[dviptr++] = push;
		if (dviptr == dvilimit)
			dviswap();
	}
	if (curs > maxpush)
		maxpush = curs;
	int saveloc = dvioffset+dviptr;
	scaled baseline = curv;
	scaled leftedge = curh;
	while (p)
		if (p >= himemmin)
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
			do
			{
				f = type(p);
				c = subtype(p);
				if (f != dvif)
				{
					if (not fontused[f])
					{
						dvifontdef(f);
						fontused[f] = true;
					}
					if (f <= 64)
					{
						dvibuf[dviptr++] = f+170;
						if (dviptr == dvilimit)
							dviswap();
					}
					else
					{
						dvibuf[dviptr++] = 235;
						if (dviptr == dvilimit)
							dviswap();
						dvibuf[dviptr++] = f-1;
						if (dviptr == dvilimit)
							dviswap();
					}
					dvif = f;
				}
				;
				if (c >= 128)
				{
					dvibuf[dviptr++] = set1;
					if (dviptr == dvilimit)
						dviswap();
				}
				dvibuf[dviptr++] = c;
				if (dviptr == dvilimit)
					dviswap();
				curh += char_width(f, char_info(f, c));
				p = link(p);
			} while (p >= himemmin);
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
					if ((ruleht == null_flag))
						ruleht = height(thisbox);
					if ((ruledp == null_flag))
						ruledp = depth(thisbox);
					ruleht += ruledp;
					if (ruleht > 0 && rulewd > 0)
					{
						if (curh != dvih)
						{
							movement(curh-dvih, 143);
							dvih = curh;
						}
						curv = baseline+ruledp;
						if (curv != dviv)
						{
							movement(curv-dviv, 157);
							dviv = curv;
						}
						dvibuf[dviptr++] = set_rule;
						if (dviptr == dvilimit)
							dviswap();
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
					rulewd += curg;
					if (subtype(p) >= 100)
					{
						halfword leaderbox = link(p+1);
						if (type(leaderbox) == 2)
						{
							ruleht = height(leaderbox);
							ruledp = depth(leaderbox);
							if ((ruleht == null_flag))
								ruleht = height(thisbox);
							if ((ruledp == null_flag))
								ruledp = depth(thisbox);
							ruleht += ruledp;
							if (ruleht > 0 && rulewd > 0)
							{
								if (curh != dvih)
								{
									movement(curh-dvih, 143);
									dvih = curh;
								}
								curv = baseline+ruledp;
								if (curv != dviv)
								{
									movement(curv-dviv, 157);
									dviv = curv;
								}
								dvibuf[dviptr++] = set_rule;
								if (dviptr == dvilimit)
									dviswap();
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
								if (curv != dviv)
								{
									movement(curv-dviv, 157);
									dviv = curv;
								}
								auto savev = dviv;
								if (curh != dvih)
								{
									movement(curh-dvih, 143);
									dvih = curh;
								}
								auto saveh = dvih;
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

