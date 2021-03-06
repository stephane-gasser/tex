#include "initmath.h"
#include "lecture.h"
#include "etat.h"
#include "linebreak.h"
#include "pushmath.h"
#include "equivalent.h" 
#include "buildpage.h"
#include "police.h"
#include "getnext.h"

void initmath(char status)
{
	scaled w, l, s;
	int n;
	scaled v, d;
	auto t = scanner.get(status);
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
			auto p = justbox->list_ptr;
			while (p)
			{
				switch (p->type)
				{
					case char_node:
						d = dynamic_cast<CharNode*>(p)->width();
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
					case hlist_node: //0
					case vlist_node: //1
					case rule_node: //2
						d = dynamic_cast<RuleNode*>(p)->width;
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
						lig_trick->font = P->font;
						lig_trick->character = P->character;
						lig_trick->link = p->link;
						p = lig_trick;
						continue;
					}
					case kern_node: //11
						d = dynamic_cast<KernNode*>(p)->width;
						break;
					case math_node: //9
						d = dynamic_cast<MathNode*>(p)->width;
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
		if (par_shape_ptr() == nullptr)
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
			int idx = par_shape_ptr()->values.size();
			idx = std::min(idx, 2*(prev_graf+2));
			s = par_shape_ptr()->values[idx-2];
			l = par_shape_ptr()->values[idx-1];
		}
		pushmath(math_shift_group);
		mode = mmode;
		eqtb_int[cur_fam_code].word_define(noPrefix, -1);
		eqtb_dimen[pre_display_size_code].word_define(noPrefix, w);
		eqtb_dimen[display_width_code].word_define(noPrefix, l);
		eqtb_dimen[display_indent_code].word_define(noPrefix, s);
		everyDisplay();
		if (nest.size() == 2)
			buildpage(status);
	}
	else
	{
		backinput(t);
		pushmath(math_shift_group);
		eqtb_int[cur_fam_code].word_define(noPrefix, -1);
		everyMath();
	}
}
