#include "hpack.h"
#include "print.h"
#include "printint.h"
#include "println.h"
#include "printscaled.h"
#include "printnl.h"
#include "shortdisplay.h"
#include "begindiagnostic.h"
#include "showbox.h"
#include "enddiagnostic.h"
#include "getnode.h"
#include "freenode.h"
#include "badness.h"
#include "newrule.h"

static void goto50(halfword r)
{
	if (outputactive)
		print(846); //) has occurred while \output is active
	else
	{
		if (packbeginline)
		{
			if (packbeginline > 0)
				print(847); //) in paragraph at lines 
			else
				print(848); //) in alignment at lines 
			printint(abs(packbeginline));
			print(849); //--
		}
		else
			print(850); //) detected at line
		printint(line);
	}
	println();
	fontinshortdisplay = 0;
	shortdisplay(link(r+5));
	println();
	begindiagnostic();
	showbox(r);
	enddiagnostic(true);
}

halfword hpack(halfword p, scaled w, smallnumber m)
{
	lastbadness = 0;
	auto r = getnode(7);
	type(r) = 0;
	subtype(r) = 0;
	mem[r+4].int_ = 0;
	auto q = r+5;
	link(q) = p;
	scaled h = 0;
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
	while (p)
	{
		scaled s;
		glueord o;
		while (p >= himemmin)
		{
			f = type(p);
			auto i = fontinfo[charbase[f]+subtype(p)].qqqq;
			eightbits hd = i.b1;
			x += fontinfo[widthbase[f]+i.b0].int_;
			s = fontinfo[heightbase[f]+hd/16].int_;
			if (s > h)
				h = s;
			s = fontinfo[depthbase[f]+hd%16].int_;
			if (s > d)
				d = s;
			p = link(p);
		}
		if (p)
		{
			switch (type(p))
			{
				case 0:
				case 1:
				case 2:
				case 13:
					x += mem[p+1].int_;
					if (type(p) >= 2)
						s = 0;
					else
						s = mem[p+4].int_;
					if (mem[p+3].int_-s > h)
						h = mem[p+3].int_-s;
					if (mem[p+2].int_+s > d)
						d = mem[p+2].int_+s;
					break;
				case 3:
				case 4:
				case 5: 
					if (adjusttail)
					{
						while (link(q) != p)
							q = link(q);
						if (type(p) == 5)
						{
							link(adjusttail) = mem[p+1].int_;
							while (link(adjusttail))
								adjusttail = link(adjusttail);
							p = link(p);
							freenode(link(q), 2);
						}
						else
						{
							link(adjusttail) = p;
							adjusttail = p;
							p = link(p);
						}
						link(q) = p;
						p = q;
					}
					break;
				case 8:
					break;
				case 10:
					g = info(p+1);
					x += mem[g+1].int_;
					o = type(g);
					totalstretch[o] += mem[g+2].int_;
					o = subtype(g);
					totalshrink[o] = totalshrink[o]+mem[g+3].int_;
					if (subtype(p) >= 100)
					{
						g = link(p+1);
						if (mem[g+3].int_ > h)
							h = mem[g+3].int_;
						if (mem[g+2].int_ > d)
							d = mem[g+2].int_;
					}
					break;
				case 11:
				case 9: 
					x += mem[p+1].int_;
					break;
				case 6:
					mem[29988] = mem[p+1];
					link(29988) = link(p);
					p = 29988;
					continue;
			}
			p = link(p);
		}
	}
	if (adjusttail)
		link(adjusttail) = 0;
	mem[r+3].int_ = h;
	mem[r+2].int_ = d;
	if (m == 1)
		w += x;
	mem[r+1].int_ = w;
	x = w-x;
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
			if (o == 0 && link(r+5) != 0)
			{
				lastbadness = badness(x, totalstretch[0]);
				if (lastbadness > int_par(hbadness_code))
				{
					println();
					if (lastbadness > 100)
						printnl(843); //Underfull
					else
					printnl(844); //Loose
					print(845); // \hbox (badness 
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
			if (totalshrink[o] < -x && o == 0 && link(r+5) != 0)
			{
				lastbadness = 1000000;
				mem[r+6].gr = 1.0;
				if (-x-totalshrink[0] > dimen_par(hfuzz_code) || int_par(hbadness_code) < 100)
				{
					if (dimen_par(overfull_rule_code) > 0 && -x-totalshrink[0] > dimen_par(hfuzz_code))
					{
						while (link(q))
							q = link(q);
						link(q) = newrule();
						mem[link(q)+1].int_ = dimen_par(overfull_rule_code);
					}
					println();
					printnl(851); //Overfull \hbox (
					printscaled(-x-totalshrink[0]);
					print(852); //pt too wide
					goto50(r);
				}
			}
			else 
				if (o == 0)
					if (link(r+5))
					{
						lastbadness = badness(-x, totalshrink[0]);
						if (lastbadness > int_par(hbadness_code))
						{
							println();
							printnl(853); //Tight \hbox (badness 
							printint(lastbadness);
							goto50(r);
						}
					}
		}
	return r;
}
