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

void goto50(halfword r)
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
	mem[r+4].int_ = 0;
	link(r+5) = p;
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
				case 0:
				case 1:
				case 2:
				case 13:
					x += d+mem[p+3].int_;
					d = mem[p+2].int_;
					if (type(p) >= 2)
						s = 0;
					else
						s = mem[p+4].int_;
					if (mem[p+1].int_+s > w)
						w = mem[p+1].int_+s;
					break;
				case 8:
					break;
				case 10:
					x += d;
					d = 0;
					g = info(p+1);
					x += mem[g+1].int_;
					o = type(g);
					totalstretch[o] += mem[g+2].int_;
					o = subtype(g);
					totalshrink[o] += mem[g+3].int_;
					if (subtype(p) >= 100)
					{
						g = link(p+1);
						if (mem[g+1].int_ > w)
							w = mem[g+1].int_;
					}
					break;
				case 11:
					x += d+mem[p+1].int_;
					d = 0;
			}
		p = link(p);
	}
	mem[r+1].int_ = w;
	if (d > l)
	{
		x += d-l;
		mem[r+2].int_ = l;
	}
	else
		mem[r+2].int_ = d;
	if (m == 1)
		h += x;
	mem[r+3].int_ = h;
	x = h-x;
	if (x == 0)
	{
		type(r+5) = 0;
		subtype(r+5) = 0;
		mem[r+6].gr = 0.0;
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
			subtype(r+5) = o;
			type(r+5) = 1;
			if (totalstretch[o])
				mem[r+6].gr = x/totalstretch[o];
			else
			{
				type(r+5) = 0;
				mem[r+6].gr = 0.0;
			}
			if (o == 0)
			if (link(r+5))
			{
				lastbadness = badness(x, totalstretch[0]);
				if (lastbadness > eqtb[5290].int_)
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
			subtype(r+5) = o;
			type(r+5) = 2;
			if (totalshrink[o])
				mem[r+6].gr = (-x)/totalshrink[o];
			else
			{
				type(r+5) = 0;
				mem[r+6].gr = 0.0;
			}
			if (totalshrink[o] < -x && o == 0 && link(r+5))
			{
				lastbadness = 1000000;
				mem[r+6].gr = 1.0;
				if (-x-totalshrink[0] > eqtb[5839].int_ || eqtb[5290].int_ < 100)
				{
					println();
					printnl(856); //6Overfull \vbox (
					printscaled(-x-totalshrink[0]);
					print(857); //pt too high
					goto50(r);
				}
			}
			else 
				if (o == 0 && link(r+5))
				{
					lastbadness = badness(-x, totalshrink[0]);
					if (lastbadness > eqtb[5290].int_)
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
