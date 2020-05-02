#include "shownodelist.h"
#include "print.h"
#include "println.h"
#include "printesc.h"
#include "printchar.h"
#include "printfontandchar.h"
#include "printcurrentstring.h"
#include "printscaled.h"
#include "printglue.h"
#include "printint.h"
#include "printspec.h"
#include "printwritewhatsit.h"
#include "printdelimiter.h"
#include "printsubsidiarydata.h"
#include "printstyle.h"
#include "printmark.h"
#include "shortdisplay.h"
#include "printskipparam.h"
#include "printruledimen.h"
#include "printfilename.h"
#include "printfamandchar.h"
#include <cmath>

void shownodelist(int p)
{
	if (poolptr - strstart[strptr] > depththreshold)
	{
		if (p > 0)
			print(314); // []
		return;
	}
	int n = 0;
	while (p > memmin)
	{
		println();
		printcurrentstring();
		if (p > memend)
		{
			print(315); //Bad link, display aborted.
			return;
		}
		n++;
		if (n > breadthmax)
		{
			print(316); //etc.
			return;
		}
		if (p >= himemmin)
			printfontandchar(p);
		else
			switch (type(p))
			{
				case 0:
				case 1:
				case 13:
					if (type(p) == 0)
						printesc('h');
					else 
						if (type(p) == 1)
							printesc('v');
						else
							printesc(318); //unset
					print(319); //box(
					printscaled(mem[p+3].int_);
					printchar('+');
					printscaled(mem[p+2].int_);
					print(320); //)x
					printscaled(mem[p+1].int_);
					if (type(p) == 13)
					{
						if (subtype(p))
						{
							print(286); // (
							printint(subtype(p)+1);
							print(322); // columns)
						}
						if (mem[p+6].int_)
						{
							print(323); //, stretch 
							printglue(mem[p+6].int_, subtype(p+5), 0);
						}
						if (mem[p+4].int_)
						{
							print(324); //, shrink 
							printglue(mem[p+4].int_, type(p+5), 0);
						}
					}
					else
					{
						g = mem[p+6].gr;
						if (g && type(p+5))
						{
							print(325); //, glue set 
							if (type(p+5) == 2)
								print(326); //- 
							if (abs(mem[p+6].int_) < 1048576)
								print(327); //?.?
							else 
								if (abs(g) > 20000.0)
								{
									if (g > 0.0)
										printchar('>');
									else
										print(328); //< -
									printglue(20000*0x1'00'00, subtype(p+5), 0);
								}
								else
									printglue(round(0x1'00'00*g), subtype(p+5), 0);
						}
						if (mem[p+4].int_)
						{
							print(321); //, shifted 
							printscaled(mem[p+4].int_);
						}
					}
					strpool[poolptr++] = '.';
					shownodelist(link(p+5));
					poolptr--;
					break;
				case 2:
					printesc(329); //rule(
					printruledimen(mem[p+3].int_);
					printchar('+');
					printruledimen(mem[p+2].int_);
					print(320); //)x
					printruledimen(mem[p+1].int_);
					break;
				case 3:
					printesc(330); //insert
					printint(subtype(p));
					print(331); //, natural size 
					printscaled(mem[p+3].int_);
					print(332); //; split(
					printspec(link(p+4), 0);
					printchar(',');
					printscaled(mem[p+2].int_);
					print(333); //); float cost 
					printint(mem[p+1].int_);
					strpool[poolptr++] = '.';
					shownodelist(info(p+4));
					poolptr--;
					break;
				case 8:
					switch (subtype(p))
					{
						case 0:
							printwritewhatsit(1284, p); //openout
							printchar('=');
							printfilename(link(p+1), info(p+2), link(p+2));
							break;
						case 1:
							printwritewhatsit(594, p); //write
							printmark(link(p+1));
							break;
						case 2: 
							printwritewhatsit(1285, p); //closeout
							break;
						case 3:
							printesc(1286); //special
							printmark(link(p+1));
							break;
						case 4:
							printesc(1288); //setlanguage
							printint(link(p+1));
							print(1291); // (hyphenmin 
							printint(type(p+1));
							printchar(',');
							printint(subtype(p+1));
							printchar(')');
							break;
						default: 
							print(1292); //whatsit?
					}
					break;
				case 10:
					if (subtype(p) >= 100)
					{
						printesc(338); //
						if (subtype(p) == 101)
							printchar('c');
						else 
							if (subtype(p) == 102)
								printchar('x');
						print(339); //leaders 
						printspec(info(p+1), 0);
						strpool[poolptr++] = '.';
						shownodelist(link(p+1));
						poolptr--;
					}
					else
					{
						printesc(334); //glue
						if (subtype(p))
						{
							printchar('(');
							if (subtype(p) < 98)
								printskipparam(subtype(p)-1);
							else 
								if (subtype(p) == 98)
								printesc(335); //nonscript
							else
								printesc(336); //mskip
							printchar(')');
						}
						if (subtype(p) != 98)
						{
							printchar(' ');
							if (subtype(p) < 98)
								printspec(info(p+1), 0);
							else
								printspec(info(p+1), 337); //mu
						}
					}
				case 11:
					if (subtype(p) != 99)
					{
						printesc(340); //kern
						if (subtype(p))
							printchar(' ');
						printscaled(mem[p+1].int_);
						if (subtype(p) == 2)
							print(341); // (for accent)
					}
					else
					{
						printesc(342); //mkern
						printscaled(mem[p+1].int_);
						print(337); //mu
					}
					break;
				case 9:
					printesc(343); //math
					if (subtype(p) == 0)
						print(344); //on
					else
						print(345); //off
					if (mem[p+1].int_)
					{
						print(346); //, surrounded 
						printscaled(mem[p+1].int_);
					}
					break;
				case 6:
					printfontandchar(p+1);
					print(347); // (ligature 
					if (subtype(p) > 1)
						printchar('|');
					fontinshortdisplay = type(p+1);
					shortdisplay(link(p+1));
					if (subtype(p)%2)
						printchar('|');
					printchar(')');
					break;
				case 12:
					printesc(348); //penalty 
					printint(mem[p+1].int_);
					break;
				case 7:
					printesc(349); //discretionary
					if (subtype(p) > 0)
					{
						print(350); // replacing 
						printint(subtype(p));
					}
					strpool[poolptr++] = '.';
					shownodelist(info(p+1));
					poolptr--;
					strpool[poolptr++] = '|';
					shownodelist(link(p+1));
					poolptr--;
					break;
				case 4:
					printesc(351); //mark
					printmark(mem[p+1].int_);
					break;
				case 5:
					printesc(352); //vadjust
					strpool[poolptr++] = '.';
					shownodelist(mem[p+1].int_);
					poolptr--;
					break;
				case 14: 
					printstyle(subtype(p));
					break;
				case 15:
					printesc(525); //mathchoice
					strpool[poolptr++] = 'D';
					shownodelist(info(p+1));
					poolptr--;
					strpool[poolptr++] = 'T';
					shownodelist(link(p+1));
					poolptr--;
					strpool[poolptr++] = 'S';
					shownodelist(info(p+2));
					poolptr--;
					strpool[poolptr++] = 's';
					shownodelist(link(p+2));
					poolptr--;
					break;
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 27:
				case 26:
				case 29:
				case 28:
				case 30:
				case 31:
					switch (type(p))
					{
						case 16: 
							printesc(865); //mathord
							break;
						case 17: 
							printesc(866); //mathop
							break;
						case 18: 
							printesc(867); //mathbin
							break;
						case 19: 
							printesc(868); //mathrel
							break;
						case 20: 
							printesc(869); //mathopen
							break;
						case 21: 
							printesc(870); //mathclose
							break;
						case 22: 
							printesc(871); //mathpunct
							break;
						case 23: 
							printesc(872); //mathinner
							break;
						case 27: 
							printesc(873); //overline
							break;
						case 26: 
							printesc(874); //underline
							break;
						case 29: 
							printesc(539); //vcenter
							break;
						case 24:
							printesc(533); //radical
							printdelimiter(p+4);
							break;
						case 28:
							printesc(508); //accent
							printfamandchar(p+4);
							break;
						case 30:
							printesc(875); //left
							printdelimiter(p+1);
							break;
						case 31:
							printesc(876); //right
							printdelimiter(p+1);
					}
					if (subtype(p))
						if (subtype(p) == 1)
							printesc(877); //limits
						else
							printesc(878); //nolimits
					if (type(p) < 30)
					printsubsidiarydata(p+1, '.');
					printsubsidiarydata(p+2, '^');
					printsubsidiarydata(p+3, '_');
					break;
				case 25:
					printesc(879); //fraction, thickness 
					if (mem[p+1].int_ == 0x40'00'00'00)
						print(880); //= default
					else
						printscaled(mem[p+1].int_);
					if (mem[p+4].qqqq.b0 || mem[p+4].qqqq.b1 || mem[p+4].qqqq.b2 || mem[p+4].qqqq.b3)
					{
						print(881); //, left-delimiter 
						printdelimiter(p+4);
					}
					if (mem[p+5].qqqq.b0 || mem[p+5].qqqq.b1 || mem[p+5].qqqq.b2 || mem[p+5].qqqq.b3)
					{
						print(882); //, right-delimiter 
						printdelimiter(p+5);
					}
					printsubsidiarydata(p+2, '\\');
					printsubsidiarydata(p+3, '/');
					break;
				default: 
					print(317); //Unknown node type!
			}
		p = link(p);
	}
}
