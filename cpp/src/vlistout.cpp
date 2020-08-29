#include "hlistout.h"
#include "vlistout.h"
#include "dvi.h"
#include "outwhat.h"
#include "erreur.h"
#include <cmath>

void vlistout(BoxNode *thisbox)
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
	auto leftedge = curh;
	curv -= thisbox->height;
	auto topedge = curv;
	while (p)
	{
		if (p->is_char_node())
			confusion("vlistout");
		else
		{
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				{
					auto P = dynamic_cast<BoxNode*>(p);
					if (P->list_ptr == nullptr)
						curv += P->height+P->depth;
					else
					{
						curv += P->height;
						if (curv != dviv)
						{
							movement(curv-dviv, down1);
							dviv = curv;
						}
						auto saveh = dvih;
						auto savev = dviv;
						curh = leftedge+P->shift_amount;
						if (p->type == vlist_node)
							vlistout(P);
						else
							hlistout(P);
						dvih = saveh;
						dviv = savev;
						curv = savev+P->depth;
						curh = leftedge;
					}
					break;
				}
				case rule_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					ruleht = P->height;
					ruledp = P->depth;
					rulewd = P->width;
					if (is_running(rulewd))
						rulewd = thisbox->width;
					ruleht += ruledp;
					curv += ruleht;
					if (ruleht > 0 &&rulewd > 0)
					{
						synch_h();
						synch_v();
						dvi_out(put_rule);
						dvifour(ruleht);
						dvifour(rulewd);
					}
					next(p);
					continue;
				}
				case whatsit_node:
					outwhat(dynamic_cast<WhatsitNode*>(p));
					break;
				case glue_node:
				{
					auto pp = dynamic_cast<GlueNode*>(p);
					auto g = pp->glue_ptr;
					ruleht = g->width-curg;
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
					ruleht += curg;
					if (pp->subtype >= a_leaders)
					{
						auto leaderbox = dynamic_cast<RuleNode*>(pp->leader_ptr);
						if (leaderbox->type == rule_node)
						{
							rulewd = leaderbox->width;
							ruledp = 0;
							if (is_running(rulewd))
								rulewd = thisbox->width;
							ruleht += ruledp;
							curv += ruleht;
							if (ruleht > 0 &&rulewd > 0)
							{
								synch_h();
								synch_v();
								dvi_out(put_rule);
								dvifour(ruleht);
								dvifour(rulewd);
							}
							next(p);
							continue;
						}
						auto leaderht = leaderbox->height+leaderbox->depth;
						if ((leaderht > 0) and (ruleht > 0))
						{
							ruleht += 10;
							auto edge = curv+ruleht;
							scaled lx = 0;
							if (pp->subtype == a_leaders)
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
								if (pp->subtype == c_leaders)
									curv += lr/2;
								else
								{
									lx = lr/(lq+1);
									curv += (lr-(lq-1)*lx)/2;
								}
							}
							while (curv+leaderht <= edge)
							{
								auto Leaderbox = dynamic_cast<BoxNode*>(leaderbox);
								curh = leftedge+Leaderbox->shift_amount;
								synch_h();
								auto saveh = dvih;
								curv += leaderbox->height;
								synch_v();
								auto savev = dviv;
								bool outerdoingleaders = doingleaders;
								doingleaders = true;
								(leaderbox->type == vlist_node ? vlistout : hlistout)(Leaderbox);
								doingleaders = outerdoingleaders;
								dviv = savev;
								dvih = saveh;
								curh = leftedge;
								curv = savev-leaderbox->height+leaderht+lx;
							}
							curv = edge-10;
							next(p);
							continue;
						}
					}
					curv = curv+ruleht;
					next(p);
					continue;
				}
				case kern_node: 
					curv += dynamic_cast<KernNode*>(p)->width;
			}
			next(p);
			continue;
		}
	}
	prunemovements(saveloc);
	if (curs > 0)
		dvipop(saveloc);
	curs--;
}
