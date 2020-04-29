#include "vertbreak.h"
#include "confusion.h"
#include "badness.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "newspec.h"
#include "deleteglueref.h"

halfword vertbreak(halfword p, scaled h, scaled d)
{
	halfword prevp, q, r;
	int pi, b, leastcost;
	halfword bestplace;
	scaled prevdp;
	smallnumber t;
	prevp = p;
	leastcost = 1073741823;
	for (int i = 1; i <= 6; i++)
		activewidth[i] = 0;
	prevdp = 0;
	while (true)
	{
		if (p == 0)
			pi = -10000;
		else
			switch (type(p))
			{
				case hlist_node: //0
				case vlist_node: //1
				case rule_node: //2
					activewidth[1] += prevdp+mem[p+3].int_;
					prevdp = mem[p+2].int_;
					break;
				case whatsit_node: //8
					break;
				case glue_node:  //10
					if (type(prevp) < 9)
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
					pi = mem[p+1].int_;
					break;
				case mark_node: //4
				case ins_node: //3
					break;
				default: 
					confusion(959); //vertbreak
			}
		if (p == 0 || (type(p) == glue_node && type(prevp) < 9) || (type(p) == kern_node && t == glue_node) || type(p) == penalty_node)
			if (pi < 10000)
			{
				if (activewidth[1] < h)
					if (activewidth[3] || activewidth[4] || activewidth[5] != 0)
						b = 0;
					else
					b = badness(h-activewidth[1], activewidth[2]);
				else 
					if (activewidth[1]-h > activewidth[6])
						b = 1073741823;
					else
						b = badness(activewidth[1]-h, activewidth[6]);
				if (b < 1073741823)
					if (pi <= -10000)
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
					bestheightplusdepth = activewidth[1]+prevdp;
				}
				if (b == 1073741823 || pi <= -10000)
					return bestplace;
			}
		if (type(p) == kern_node)
		{
			q = p;
			activewidth[1] += prevdp+mem[q+1].int_;
			prevdp = 0;
		}
		if (type(p) == glue_node)
		{
			q = info(p+1);
			activewidth[2+type(q)] = activewidth[2+type(q)]+mem[q+2].int_;
			activewidth[6] += mem[q+3].int_;
			if (subtype(q) && mem[q+3].int_)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(960); //Infinite glue shrinkage found in box being split
				helpptr = 4;
				helpline[3] = 961; //The box you are \vsplitting contains some infinitely
				helpline[2] = 962; //shrinkable glue, e.g., `\vss' or `\vskip 0pt minus 1fil'.
				helpline[1] = 963; //Such glue doesn't belong there; but you can safely proceed,
				helpline[0] = 921; //since the offensive shrinkability has been made finite.
				error();
				r = newspec(q);
				subtype(r) = 0;
				deleteglueref(q);
				info(p+1) = r;
				q = r;
			}
			activewidth[1] += prevdp+mem[q+1].int_;
			prevdp = 0;
		}
		if (prevdp > d)
		{
			activewidth[1] += prevdp-d;
			prevdp = d;
		}
		prevp = p;
		p = link(prevp);
	}
	return bestplace;
}
