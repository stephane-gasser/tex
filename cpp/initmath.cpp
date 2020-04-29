#include "initmath.h"
#include "gettoken.h"
#include "popnest.h"
#include "linebreak.h"
#include "pushmath.h"
#include "eqworddefine.h"
#include "begintokenlist.h"
#include "buildpage.h"
#include "backinput.h"

void initmath(void)
{
	scaled w, l, s;
	halfword p, q;
	internalfontnumber f;
	int n;
	scaled v, d;
	gettoken();
	if (curcmd == 3 &&curlist.modefield > 0)
	{
		if (curlist.headfield == curlist.tailfield)
		{
			popnest();
			w = -1073741823;
		}
		else
		{
			linebreak(eqtb[5270].int_);
			v = mem[justbox+4].int_+2*fontinfo[6+parambase[eqtb[3934].hh.rh]].int_;
			w = -1073741823;
			p = link(justbox+5);
			while (p)
			{
				if (p >= himemmin)
				{
					f = type(p);
					d = fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(p)].qqqq.b0].int_;
					if (v < 1073741823)
					{
						v += d;
						w = v;
					}
					else
					{
						w = 1073741823;
						break;
					}
					p = link(p);
					continue;
				}
				switch (type(p))
				{
					case hlist_node: //0
					case vlist_node: //1
					case rule_node: //2
						d = mem[p+1].int_;
						if (v < 1073741823)
						{
							v += d;
							w = v;
						}
						else
						{
							w = 1073741823;
							break;
						}
						p = link(p);
						continue;
					case ligature_node: //6
						mem[29988] = mem[p+1];
						link(29988) = link(p);
						p = 29988;
						continue;
					case kern_node: //11
					case math_node: //9
						d = mem[p+1].int_;
						break;
					case glue_node: //10
						q = info(p+1);
						d = mem[q+1].int_;
						if (type(justbox+5) == 1)
						{
							if (subtype(justbox+5) == type(q) && mem[q+2].int_)
								v = 1073741823;
						}
						else 
							if (type(justbox+5) == 2)
								if (subtype(justbox+5) == subtype(q) && mem[q+3].int_)
									v = 1073741823;
						if (subtype(p) >= 100)
						{
							if (v < 1073741823)
							{
								v += d;
								w = v;
							}
							else
							{
								w = 1073741823;
								break;
							}
							p = link(p);
							continue;
						}
						break;
					case whatsit_node: //8
						d = 0;
						break;
					default: 
						d = 0;
				}
				if (v < 1073741823)
					v += d;
				p = link(p);
				continue;
			}
		}
		if (eqtb[3412].hh.rh == 0)
			if (eqtb[5847].int_ && ((eqtb[5304].int_ >= 0 && curlist.pgfield+2 > eqtb[5304].int_) || curlist.pgfield+1 < -eqtb[5304].int_))
			{
				l = eqtb[5833].int_-abs(eqtb[5847].int_);
				if (eqtb[5847].int_ > 0)
					s = eqtb[5847].int_;
				else
					s = 0;
			}
			else
			{
				l = eqtb[5833].int_;
				s = 0;
			}
		else
		{
			n = info(eqtb[3412].hh.rh);
			if (curlist.pgfield+2 >= n)
				p = eqtb[3412].hh.rh+2*n;
			else
				p = eqtb[3412].hh.rh+2*(curlist.pgfield+2);
			s = mem[p-1].int_;
			l = mem[p].int_;
		}
		pushmath(15);
		curlist.modefield = 203;
		eqworddefine(5307, -1);
		eqworddefine(5843, w);
		eqworddefine(5844, l);
		eqworddefine(5845, s);
		if (eqtb[3416].hh.rh)
			begintokenlist(eqtb[3416].hh.rh, 9);
		if (nestptr == 1)
			buildpage();
	}
	else
	{
		backinput();
		pushmath(15);
		eqworddefine(5307, -1);
		if (eqtb[3415].hh.rh)
			begintokenlist(eqtb[3415].hh.rh, 8);
	}
}
