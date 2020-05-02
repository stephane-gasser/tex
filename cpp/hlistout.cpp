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
				curh += fontinfo[widthbase[f]+fontinfo[charbase[f]+c].qqqq.b0].int_;
				p = link(p);
			} while (p >= himemmin);
			dvih = curh;
		}
		else
		{
			switch (type(p))
			{
				case 0:
				case 1:
					if (link(p+5) == 0)
						curh = curh+mem[p+1].int_;
					else
					{
						auto saveh = dvih;
						auto savev = dviv;
						curv = baseline+mem[p+4].int_;
						tempptr = p;
						auto edge = curh;
						if (type(p) == 1)
							vlistout();
						else
							hlistout();
						dvih = saveh;
						dviv = savev;
						curh = edge+mem[p+1].int_;
						curv = baseline;
					}
					break;
				case 2:
					ruleht = mem[p+3].int_;
					ruledp = mem[p+2].int_;
					rulewd = mem[p+1].int_;
					if ((ruleht == -0x40'00'00'00))
						ruleht = mem[thisbox+3].int_;
					if ((ruledp == -0x40'00'00'00))
						ruledp = mem[thisbox+2].int_;
					ruleht = ruleht+ruledp;
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
				case 8:
					outwhat(p);
					break;
				case 10:
					g = info(p+1);
					rulewd = mem[g+1].int_-curg;
					if (gsign != 0)
						if (gsign == 1)
						{
							if (type(g) == gorder)
							{
								curglue = curglue+mem[g+2].int_;
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
								curglue = curglue-mem[g+3].int_;
								float gluetemp = mem[thisbox+6].gr*curglue;
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
							ruleht = mem[leaderbox+3].int_;
							ruledp = mem[leaderbox+2].int_;
							if ((ruleht == -0x40'00'00'00))
								ruleht = mem[thisbox+3].int_;
							if ((ruledp == -0x40'00'00'00))
								ruledp = mem[thisbox+2].int_;
							ruleht = ruleht+ruledp;
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
						scaled leaderwd = mem[leaderbox+1].int_;
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
								curv = baseline+mem[leaderbox+4].int_;
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
				case 11:
				case 9: 
					curh = curh+mem[p+1].int_;
					break;
				case 6:
					mem[lig_trick] = mem[p+1];
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

