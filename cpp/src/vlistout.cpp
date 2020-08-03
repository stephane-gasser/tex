#include "hlistout.h"
#include "dviswap.h"
#include "movement.h"
#include "prunemovements.h"
#include "dvifontdef.h"
#include "dvifour.h"
#include "vlistout.h"
#include "dvipop.h"
#include "outwhat.h"
#include "erreur.h"
#include <cmath>

void vlistout(void)
{
	scaled curg = 0;
	float curglue = 0.0;
	auto thisbox = tempptr;
	glueord gorder = glue_order(thisbox);
	char gsign = glue_sign(thisbox);
	LinkedNode *p;
	p->num = list_ptr(thisbox);
	curs++;
	if (curs > 0)
		dvi_out(push);
	if (curs > maxpush)
		maxpush = curs;
	int saveloc = dvioffset+dviptr;
	auto leftedge = curh;
	curv -= height(thisbox);
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
					if (list_ptr(p->num) == 0)
						curv += height(p->num)+depth(p->num);
					else
					{
						curv += height(p->num);
						if (curv != dviv)
						{
							movement(curv-dviv, down1);
							dviv = curv;
						}
						auto saveh = dvih;
						auto savev = dviv;
						curh = leftedge+shift_amount(p->num);
						tempptr = p->num;
						if (p->type == vlist_node)
							vlistout();
						else
							hlistout();
						dvih = saveh;
						dviv = savev;
						curv = savev+depth(p->num);
						curh = leftedge;
					}
					break;
				case rule_node:
					ruleht = height(p->num);
					ruledp = depth(p->num);
					rulewd = width(p->num);
					if (is_running(rulewd))
						rulewd = width(thisbox);
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
					p = p->link;
					continue;
				case whatsit_node:
					outwhat(p->num);
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
								curg = round(vet_glue(glue_set(thisbox)*curglue));
							}
						}
						else 
							if (g->shrink_order == gorder)
							{
								curglue -= g->shrink;
								curg = round(vet_glue(glue_set(thisbox)*curglue));
							}
					ruleht += curg;
					if (pp->subtype >= a_leaders)
					{
						auto leaderbox = pp->leader_ptr;
						if (leaderbox->type == rule_node)
						{
							rulewd = width(leaderbox->num);
							ruledp = 0;
							if (is_running(rulewd))
								rulewd = width(thisbox);
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
							p = p->link;
							continue;
						}
						auto leaderht = height(leaderbox->num)+depth(leaderbox->num);
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
								curh = leftedge+shift_amount(leaderbox->num);
								synch_h();
								auto saveh = dvih;
								curv += height(leaderbox->num);
								synch_v();
								auto savev = dviv;
								tempptr = leaderbox->num;
								bool outerdoingleaders = doingleaders;
								doingleaders = true;
								if (leaderbox->type == vlist_node)
									vlistout();
								else
									hlistout();
								doingleaders = outerdoingleaders;
								dviv = savev;
								dvih = saveh;
								curh = leftedge;
								curv = savev-height(leaderbox->num)+leaderht+lx;
							}
							curv = edge-10;
							p = p->link;
							continue;
						}
					}
					curv = curv+ruleht;
					p = p->link;
					continue;
				}
				case kern_node: 
					curv += dynamic_cast<KernNode*>(p)->width;
			}
			p = p->link;
			continue;
		}
	}
	prunemovements(saveloc);
	if (curs > 0)
		dvipop(saveloc);
	curs--;
}
