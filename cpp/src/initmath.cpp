#include "initmath.h"
#include "lecture.h"
#include "popnest.h"
#include "linebreak.h"
#include "pushmath.h"
#include "eqworddefine.h"
#include "buildpage.h"
#include "backinput.h"
#include "police.h"

static int display_widow_penalty(void) { return int_par(display_widow_penalty_code); } 

//static halfword& every_display(void) { return equiv(every_display_loc); }
static TokenNode disp;
static TokenNode *every_display(void) { return &disp; }

void initmath(void)
{
	scaled w, l, s;
	LinkedNode *p;
	int n;
	scaled v, d;
	auto t = gettoken();
	if (t.cmd == math_shift && mode > 0)
	{
		if (head == tail)
		{
			popnest();
			w = -max_dimen;
		}
		else
		{
			linebreak(display_widow_penalty());
			v = justbox->shift_amount+2*cur_font().quad();
			w = -max_dimen;
			p = justbox->list_ptr;
			while (p)
			{
				if (p->is_char_node())
				{
					auto c = dynamic_cast<CharNode*>(p);
					auto ft = c->font;
					d = ft.char_width(c->character);
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
					next(p);
					continue;
				}
				switch (p->type)
				{
					case hlist_node: //0
					case vlist_node: //1
					case rule_node: //2
						d = width(p->num);
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
						next(p);
						continue;
					case ligature_node:
					{
						auto P = dynamic_cast<LigatureNode*>(p);
						lig_trick->font = P->lig_char.font;
						lig_trick->character = P->lig_char.character;
						lig_trick->link = p->link;
						p = lig_trick;
						continue;
					}
					case kern_node: //11
						d = dynamic_cast<KernNode*>(p)->width;
						break;
					case math_node: //9
						d = width(p->num);
						break;
					case glue_node: //10
					{
						auto g = dynamic_cast<GlueNode*>(p);
						auto q = g->glue_ptr;
						d = q->width;
						if (justbox->glue_sign == stretching)
						{
							if (justbox->glue_order == q->stretch_order && q->stretch)
								v = max_dimen;
						}
						else 
							if (justbox->glue_sign == shrinking)
								if (justbox->glue_order == q->shrink_order && q->shrink)
									v = max_dimen;
						if (g->subtype >= a_leaders)
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
							next(p);
							continue;
						}
						break;
					}
					case whatsit_node: //8
						d = 0;
						break;
					default: 
						d = 0;
				}
				if (v < max_dimen)
					v += d;
				next(p);
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
				p->num = par_shape_ptr()+2*n;
			else
				p->num = par_shape_ptr()+2*(prev_graf+2);
			s = mem[p->num-1].int_;
			l = mem[p->num].int_;
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
			buildpage();
	}
	else
	{
		backinput(t);
		pushmath(math_shift_group);
		eqworddefine(int_base+cur_fam_code, -1);
		if (every_math())
			begintokenlist(every_math(), 8);
	}
}
