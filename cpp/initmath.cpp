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
			linebreak(int_par(display_widow_penalty_code));
			v = mem[justbox+4].int_+2*fontinfo[6+parambase[cur_font()]].int_;
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
						mem[lig_trick] = mem[p+1];
						link(lig_trick) = link(p);
						p = lig_trick;
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
		if (par_shape_ptr() == 0)
			if (dimen_par(hang_indent_code) && ((int_par(hang_after_code) >= 0 && curlist.pgfield+2 > int_par(hang_after_code)) || curlist.pgfield+1 < -int_par(hang_after_code)))
			{
				l = dimen_par(hsize_code)-abs(dimen_par(hang_indent_code));
				if (dimen_par(hang_indent_code) > 0)
					s = dimen_par(hang_indent_code);
				else
					s = 0;
			}
			else
			{
				l = dimen_par(hsize_code);
				s = 0;
			}
		else
		{
			n = info(par_shape_ptr());
			if (curlist.pgfield+2 >= n)
				p = par_shape_ptr()+2*n;
			else
				p = par_shape_ptr()+2*(curlist.pgfield+2);
			s = mem[p-1].int_;
			l = mem[p].int_;
		}
		pushmath(15);
		curlist.modefield = 203;
		eqworddefine(5307, -1);
		eqworddefine(5843, w);
		eqworddefine(5844, l);
		eqworddefine(5845, s);
		if (every_display())
			begintokenlist(every_display(), 9);
		if (nestptr == 1)
			buildpage();
	}
	else
	{
		backinput();
		pushmath(15);
		eqworddefine(5307, -1);
		if (every_math())
			begintokenlist(every_math(), 8);
	}
}
