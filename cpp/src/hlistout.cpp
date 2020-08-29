#include "hlistout.h"
#include "dvi.h"
#include "vlistout.h"
#include "outwhat.h"
#include "police.h"
#include <cmath>

void hlistout(BoxNode *thisbox)
{
	scaled curg = 0;
	float curglue = 0.0;
	glueord gorder = thisbox->glue_order;
	char gsign = thisbox->glue_sign;
	auto p = thisbox->list_ptr;
	curs++;
	if (curs > 0)
		dvi_out(push);
	if (curs > maxpush)
		maxpush = curs;
	int saveloc = dvioffset+dviptr;
	scaled baseline = curv;
	scaled leftedge = curh;
	while (p)
		if (p->is_char_node())
		{
			synch_h();
			synch_v();
			auto P = dynamic_cast<CharNode*>(p);
			for (; p->is_char_node(); next(p))
			{
				auto ft = P->font;
				c = P->character;
				if (f != dvif)
				{
					if (!ft.used)
					{
						dvifontdef(f);
						ft.used = true;
					}
					if (f <= 64+font_base)
						dvi_out(f-font_base-1+fnt_num_0);
					else
					{
						dvi_out(fnt1);
						dvi_out(f-font_base-1);
					}
					dvif = f;
				}
				;
				if (c >= 128)
					dvi_out(set1);
				dvi_out(c);
				curh += ft.char_width(c);
			}
			dvih = curh;
		}
		else
		{
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				{
					auto P = dynamic_cast<BoxNode*>(p);
					if (P->list_ptr->num == hlist_node)
						curh += P->width;
					else
					{
						auto saveh = dvih;
						auto savev = dviv;
						curv = baseline+P->shift_amount;
						auto edge = curh;
						if (P->type == vlist_node)
							vlistout(P);
						else
							hlistout(P);
						dvih = saveh;
						dviv = savev;
						curh = edge+P->width;
						curv = baseline;
					}
					break;
				}
				case rule_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					ruleht = P->height;
					ruledp = P->depth;
					rulewd = P->width;
					if (is_running(ruleht))
						ruleht = thisbox->height;
					if (is_running(ruledp))
						ruledp = thisbox->depth;
					ruleht += ruledp;
					if (ruleht > 0 && rulewd > 0)
					{
						synch_h();
						curv = baseline+ruledp;
						synch_v();
						dvi_out(set_rule);
						dvifour(ruleht);
						dvifour(rulewd);
						curv = baseline;
						dvih = dvih+rulewd;
					}
					curh = curh+rulewd;
					next(p);
					continue;
				}
				case whatsit_node:
					outwhat(dynamic_cast<WhatsitNode*>(p));
					break;
				case glue_node:
				{
					auto P = dynamic_cast<GlueNode*>(p);
					auto g = P->glue_ptr;
					rulewd = g->width-curg;
					if (gsign)
						if (gsign == 1)
						{
							if (g->stretch_order == gorder)
							{
								curglue += g->stretch;
								curg = round(vet_glue(thisbox->glue_set*curglue));
							}
						}
						else 
							if (g->shrink_order == gorder)
							{
								curglue -= g->shrink;
								curg = round(vet_glue(thisbox->glue_set*curglue));
							}
					rulewd += curg;
					if (P->subtype >= a_leaders)
					{
						auto leaderbox = dynamic_cast<BoxNode*>(P->leader_ptr);
						if (leaderbox->type == rule_node)
						{
							ruleht = leaderbox->height;
							ruledp = leaderbox->depth;
							if (is_running(ruleht))
								ruleht = thisbox->height;
							if (is_running(ruledp))
								ruledp = thisbox->depth;
							ruleht += ruledp;
							if (ruleht > 0 && rulewd > 0)
							{
								synch_h();
								curv = baseline+ruledp;
								synch_v();
								dvi_out(set_rule);
								dvifour(ruleht);
								dvifour(rulewd);
								curv = baseline;
								dvih = dvih+rulewd;
							}
							curh = curh+rulewd;
							next(p);
							continue;
						}
						scaled leaderwd = leaderbox->width;
						if (leaderwd > 0 && rulewd > 0)
						{
							rulewd = rulewd+10;
							auto edge = curh+rulewd;
							scaled lx = 0;
							if (P->subtype == a_leaders)
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
								if (P->subtype == c_leaders)
									curh += lr/2;
								else
								{
									lx = lr/(lq+1);
									curh += (lr-(lq-1)*lx)/2;
								}
							}
							while (curh+leaderwd <= edge)
							{
								curv = baseline+leaderbox->shift_amount;
								synch_v();
								auto savev = dviv;
								synch_h();
								auto saveh = dvih;
								bool outerdoingleaders = doingleaders;
								doingleaders = true;
								if (leaderbox->type == vlist_node)
									vlistout(leaderbox);
								else
									hlistout(leaderbox);
								doingleaders = outerdoingleaders;
								dviv = savev;
								dvih = saveh;
								curv = baseline;
								curh = saveh+leaderwd+lx;
							}
							curh = edge-10;
							next(p);
							continue;
						}
					}
					curh = curh+rulewd;
					next(p);
					continue;
				}
				case kern_node:
					curh += dynamic_cast<KernNode*>(p)->width;
					break;
				case math_node: 
					curh += dynamic_cast<MathNode*>(p)->width;
					break;
				case ligature_node:
				{
					auto P = dynamic_cast<LigatureNode*>(p);
					lig_trick->font = P->lig_char.font;
					lig_trick->character = P->lig_char.character;
					lig_trick->link = p->link;
					p = lig_trick;
					continue;
				}
			}
			next(p);
			continue;
		}
	prunemovements(saveloc);
	if (curs > 0)
		dvipop(saveloc);
	curs--;
}

