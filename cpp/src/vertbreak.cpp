#include "vertbreak.h"
#include "confusion.h"
#include "badness.h"
#include "impression.h"
#include "erreur.h"
#include "newspec.h"
#include "deleteglueref.h"
#include "texte.h"

scaled *active_height = active_height; //!< new name for the six distance variables
scaled &cur_height = active_height[1]; //!< the natural height

//! initialize the height to zero
static void set_height_zero(int i) { active_height[i] = 0; }

static void erreurVertbreak(void)
{
	print_err("Infinite glue shrinkage found in box being split"); 
	helpptr = 4;
	helpline[3] = "The box you are \\vsplitting contains some infinitely";
	helpline[2] = "shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.";
	helpline[1] = "Such glue doesn't belong there; but you can safely proceed,";
	helpline[0] = "since the offensive shrinkability has been made finite.";
	error();
}

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
					pi = penalty(p);
					break;
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
			q = info(p+1);
			active_height[2+stretch_order(q)] += stretch(q);
			active_height[6] += shrink(q);
			if (shrink_order(q) && shrink(q))
			{
				erreurVertbreak();
				r = newspec(q);
				subtype(r) = 0;
				deleteglueref(q);
				info(p+1) = r;
				q = r;
			}
			cur_height += prevdp+width(q);
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
