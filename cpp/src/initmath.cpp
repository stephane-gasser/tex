#include "initmath.h"
#include "lecture.h"
#include "popnest.h"
#include "linebreak.h"
#include "pushmath.h"
#include "eqworddefine.h"
#include "buildpage.h"
#include "backinput.h"

static int display_widow_penalty(void) { return int_par(display_widow_penalty_code); }
static halfword& every_display(void) { return equiv(every_display_loc); }

void initmath(halfword align)
{
	scaled w, l, s;
	halfword p, q;
	internalfontnumber f;
	int n;
	scaled v, d;
	auto [cmd, chr, tok, cs] = gettoken(align);
	if (cmd == math_shift && mode > 0)
	{
		if (head == tail)
		{
			popnest();
			w = -max_dimen;
		}
		else
		{
			linebreak(display_widow_penalty());
			v = shift_amount(justbox)+2*quad(cur_font());
			w = -max_dimen;
			p = list_ptr(justbox);
			while (p)
			{
				if (p >= himemmin)
				{
					f = type(p);
					d = char_width(f, char_info(f, character(p)));
					if (v < max_dimen)
					{
						v += d;
						w = v;
					}
					else
					{
						w = max_dimen;
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
						d = width(p);
						if (v < max_dimen)
						{
							v += d;
							w = v;
						}
						else
						{
							w = max_dimen;
							break;
						}
						p = link(p);
						continue;
					case ligature_node: //6
						mem[lig_trick] = mem[lig_char(p)];
						link(lig_trick) = link(p);
						p = lig_trick;
						continue;
					case kern_node: //11
					case math_node: //9
						d = width(p);
						break;
					case glue_node: //10
						q = glue_ptr(p);
						d = width(q);
						if (glue_sign(justbox) == stretching)
						{
							if (glue_order(justbox) == stretch_order(q) && stretch(q))
								v = max_dimen;
						}
						else 
							if (glue_sign(justbox) == shrinking)
								if (glue_order(justbox) == shrink_order(q) && shrink(q))
									v = max_dimen;
						if (subtype(p) >= a_leaders)
						{
							if (v < max_dimen)
							{
								v += d;
								w = v;
							}
							else
							{
								w = max_dimen;
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
				if (v < max_dimen)
					v += d;
				p = link(p);
				continue;
			}
		}
		if (par_shape_ptr() == 0)
			if (hang_indent() && ((hang_after() >= 0 && prev_graf+2 > hang_after()) || prev_graf+1 < -hang_after()))
			{
				l = hsize()-abs(hang_indent());
				s = std::max(hang_indent(), 0);
			}
			else
			{
				l = hsize();
				s = 0;
			}
		else
		{
			n = info(par_shape_ptr());
			if (prev_graf+2 >= n)
				p = par_shape_ptr()+2*n;
			else
				p = par_shape_ptr()+2*(prev_graf+2);
			s = mem[p-1].int_;
			l = mem[p].int_;
		}
		pushmath(math_shift_group);
		mode = mmode;
		eqworddefine(int_base+cur_fam_code, -1);
		eqworddefine(dimen_base+pre_display_size_code, w);
		eqworddefine(dimen_base+display_width_code, l);
		eqworddefine(dimen_base+display_indent_code, s);
		if (every_display())
			begintokenlist(every_display(), 9);
		if (nestptr == 1)
			buildpage(align);
	}
	else
	{
		backinput(tok);
		pushmath(math_shift_group);
		eqworddefine(int_base+cur_fam_code, -1);
		if (every_math())
			begintokenlist(every_math(), 8);
	}
}
