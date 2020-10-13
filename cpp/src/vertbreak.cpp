#include "vertbreak.h"
#include "badness.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"

scaled active_height[7]; //=activewidth //!< new name for the six distance variables
scaled &cur_height = active_height[1]; //!< the natural height

//! initialize the height to zero
static void set_height_zero(int i) { active_height[i] = 0; }

LinkedNode *vertbreak(LinkedNode *p, scaled h, scaled d)
{
	LinkedNode *prevp = p, *q, *r;
	int pi, b;
	LinkedNode *bestplace;
	smallnumber t;
	int leastcost = max_dimen;
	for (int i = 1; i <= 6; i++)
		set_height_zero(i);
	scaled prevdp = 0;
	for (; true; next(p))
	{
		if (p == nullptr)
			pi = eject_penalty;
		else
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				case rule_node: 
					cur_height += prevdp+p->getHeight();
					prevdp = p->getDepth();
					break;
				case whatsit_node:
					break;
				case glue_node:
					if (precedes_break(prevp))
						pi = 0;
					break;
				case kern_node:
					t = p->link == nullptr ? penalty_node : p->link->type;
					if (t == glue_node)
						pi = 0;
					break;
				case penalty_node:
					pi = p->getPenalty();
					break;
				case mark_node:
				case ins_node:
					break;
				default: 
					confusion("vertbreak");
			}
		if (p == nullptr || (p->type == glue_node && precedes_break(prevp)) || (p->type == kern_node && t == glue_node) || p->type == penalty_node)
			if (pi < 10000)
			{
				if (cur_height < h)
					b = active_height[3] || active_height[4] || active_height[5] ? 0 : badness(h-cur_height, active_height[2]);
				else 
					b = cur_height-h > active_height[6] ? max_dimen : badness(cur_height-h, active_height[6]);
				if (b < awful_bad)
					b = pi <= eject_penalty ? pi : b < 10000 ? b+pi : 100000;
				if (b <= leastcost)
				{
					bestplace = p;
					leastcost = b;
					bestheightplusdepth = cur_height+prevdp;
				}
				if (b == awful_bad || pi <= eject_penalty)
					return bestplace;
			}
		if (p->type == kern_node)
		{
			q = p;
			cur_height += prevdp+q->getWidth();
			prevdp = 0;
		}
		if (p->type == glue_node)
		{
			auto P = dynamic_cast<GlueNode*>(p);
			auto q = P->glue_ptr;
			active_height[2+q->stretch_order] += q->stretch;
			active_height[6] += q->shrink;
			if (q->shrink_order && q->shrink)
			{
				error("Infinite glue shrinkage found in box being split", "The box you are \\vsplitting contains some infinitely\nshrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.\nSuch glue doesn't belong there; but you can safely proceed,\nsince the offensive shrinkability has been made finite.");
				auto r = new GlueSpec(q);
				r->shrink_order = 0;
				deleteglueref(q);
				P->glue_ptr = r;
				q = r;
			}
			cur_height += prevdp+q->width;
			prevdp = 0;
		}
		if (prevdp > d)
		{
			cur_height += prevdp-d;
			prevdp = d;
		}
		prevp = p;
	}
	return bestplace;
}
