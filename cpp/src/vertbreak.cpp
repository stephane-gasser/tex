#include "vertbreak.h"
#include "badness.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "texte.h"

scaled *active_height = active_height; //!< new name for the six distance variables
scaled &cur_height = active_height[1]; //!< the natural height

//! initialize the height to zero
static void set_height_zero(int i) { active_height[i] = 0; }

halfword vertbreak(halfword p, scaled h, scaled d)
{
	halfword prevp, q, r;
	int pi, b, leastcost;
	halfword bestplace;
	scaled prevdp;
	smallnumber t;
	prevp = p;
	leastcost = max_dimen;
	for (int i = 1; i <= 6; i++)
		set_height_zero(i);
	prevdp = 0;
	while (true)
	{
		if (p == 0)
			pi = eject_penalty;
		else
			switch (type(p))
			{
				case hlist_node: //0
				case vlist_node: //1
				case rule_node: //2
					cur_height += prevdp+height(p);
					prevdp = depth(p);
					break;
				case whatsit_node: //8
					break;
				case glue_node:  //10
					if (precedes_break(prevp))
						pi = 0;
					break;
				case kern_node: //11
					if (link(p) == 0)
						t = penalty_node; //12
					else
						t = type(link(p));
					if (t == glue_node) //10
						pi = 0;
					break;
				case penalty_node: //12
				{
					PenaltyNode *P;
					P->num = p;
					pi = P->penalty;
					break;
				}
				case mark_node: //4
				case ins_node: //3
					break;
				default: 
					confusion("vertbreak");
			}
		if (p == 0 || (type(p) == glue_node && type(prevp) < 9) || (type(p) == kern_node && t == glue_node) || type(p) == penalty_node)
			if (pi < 10000)
			{
				if (cur_height < h)
					if (active_height[3] || active_height[4] || active_height[5])
						b = 0;
					else
					b = badness(h-cur_height, active_height[2]);
				else 
					if (cur_height-h > active_height[6])
						b = max_dimen;
					else
						b = badness(cur_height-h, active_height[6]);
				if (b < awful_bad)
					if (pi <= eject_penalty)
						b = pi;
					else 
						if (b < 10000)
							b += pi;
						else
							b = 100000;
				if (b <= leastcost)
				{
					bestplace = p;
					leastcost = b;
					bestheightplusdepth = cur_height+prevdp;
				}
				if (b == awful_bad || pi <= eject_penalty)
					return bestplace;
			}
		if (type(p) == kern_node)
		{
			q = p;
			cur_height += prevdp+width(q);
			prevdp = 0;
		}
		if (type(p) == glue_node)
		{
			GlueNode *P;
			P->num = p;
			auto q = P->glue_ptr;
			active_height[2+q->stretch_order] += q->stretch;
			active_height[6] += q->shrink;
			if (q->shrink_order && q->shrink)
			{
				error("Infinite glue shrinkage found in box being split", "The box you are \\vsplitting contains some infinitely\nshrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.\nSuch glue doesn't belong there; but you can safely proceed,\nsince the offensive shrinkability has been made finite.");
				auto r = newspec(q);
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
		p = link(prevp);
	}
	return bestplace;
}
