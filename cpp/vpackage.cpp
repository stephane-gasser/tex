#include "vpackage.h"
#include "print.h"
#include "printint.h"
#include "println.h"
#include "printscaled.h"
#include "printnl.h"
#include "shortdisplay.h"
#include "begindiagnostic.h"
#include "showbox.h"
#include "enddiagnostic.h"
#include "confusion.h"
#include "getnode.h"
#include "freenode.h"
#include "badness.h"
/*#include "newrule.h"*/

static void goto50(halfword r)
{
	if (outputactive)
		print(846); //) has occurred while \output is active
	else
	{
		if (packbeginline)
		{
			print(848); //) in alignment at lines 
			printint(abs(packbeginline));
			print(849); //--
		}
		else
			print(850); //) detected at line 
		printint(line);
		println();
	}
	begindiagnostic();
	showbox(r);
	enddiagnostic(true);
}

halfword vpackage(halfword p, scaled h, smallnumber m, scaled l)
{
	lastbadness = 0;
	auto r = getnode(7);
	type(r) = 1;
	subtype(r) = 0;
	shift_amount(r) = 0;
	list_ptr(r) = p;
	scaled w = 0;
	scaled d = 0;
	scaled x = 0;
	totalstretch[0] = 0;
	totalshrink[0] = 0;
	totalstretch[1] = 0;
	totalshrink[1] = 0;
	totalstretch[2] = 0;
	totalshrink[2] = 0;
	totalstretch[3] = 0;
	totalshrink[3] = 0;
	scaled s;
	glueord o;
	while (p)
	{
		if (p >= himemmin)
			confusion(854); //vpack
		else
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case rule_node:
				case unset_node:
					x += d+height(p);
					d = depth(p);
					if (type(p) >= rule_node) // rule_node ou unset_node
						s = 0;
					else
						s = shift_amount(p);
					if (width(p)+s > w)
						w = width(p)+s;
					break;
				case whatsit_node:
					break;
				case glue_node:
					x += d;
					d = 0;
					g = glue_ptr(p);
					x += width(g);
					o = type(g);
					totalstretch[o] += stretch(g);
					o = subtype(g);
					totalshrink[o] += shrink(g);
					if (subtype(p) >= 100)
					{
						g = glue_ptr(p);
						if (width(g) > w)
							w = width(g);
					}
					break;
				case kern_node:
					x += d+width(p);
					d = 0;
			}
		p = link(p);
	}
	width(r) = w;
	if (d > l)
	{
		x += d-l;
		depth(r) = l;
	}
	else
		depth(r) = d;
	if (m == 1)
		h += x;
	height(r) = h;
	x = h-x;
	if (x == 0)
	{
		glue_sign(r) = normal;
		glue_order(r) = 0;
		glue_set(r) = 0.0;
	}
	else 
		if (x > 0)
		{
			glueord o;
			if (totalstretch[3])
				o = 3;
			else 
				if (totalstretch[2])
					o = 2;
				else 
					if (totalstretch[1])
						o = 1;
					else 
						o = 0;
			glue_order(r) = o;
			glue_sign(r) = stretching;
			if (totalstretch[o])
				glue_set(r) = x/totalstretch[o];
			else
			{
				glue_sign(r) = normal;
				glue_set(r) = 0.0;
			}
			if (o == 0)
			if (list_ptr(r))
			{
				lastbadness = badness(x, totalstretch[0]);
				if (lastbadness > int_par(vbadness_code))
				{
					println();
					if (lastbadness > 100)
						printnl(843); //Underfull
					else
						printnl(844); //Loose
					print(855); //\vbox (badness 
					printint(lastbadness);
					goto50(r);
				}
			}
		}
		else
		{
			glueord o;
			if (totalshrink[3])
				o = 3;
			else 
				if (totalshrink[2])
					o = 2;
				else 
					if (totalshrink[1])
						o = 1;
					else
						o = 0;
			glue_order(r) = o;
			glue_sign(r) = shrinking;
			if (totalshrink[o])
				glue_set(r) = (-x)/totalshrink[o];
			else
			{
				glue_sign(r) = normal;
				glue_set(r) = 0.0;
			}
			if (totalshrink[o] < -x && o == 0 && list_ptr(r))
			{
				lastbadness = 1000000;
				glue_set(r) = 1.0;
				if (-x-totalshrink[0] > dimen_par(vfuzz_code) || int_par(vbadness_code) < 100)
				{
					println();
					printnl(856); //6Overfull \vbox (
					printscaled(-x-totalshrink[0]);
					print(857); //pt too high
					goto50(r);
				}
			}
			else 
				if (o == 0 && list_ptr(r))
				{
					lastbadness = badness(-x, totalshrink[0]);
					if (lastbadness > int_par(vbadness_code))
					{
						println();
						printnl(858); //Tight \vbox (badness 
						printint(lastbadness);
						goto50(r);
					}
				}
		}
	return r;
}
