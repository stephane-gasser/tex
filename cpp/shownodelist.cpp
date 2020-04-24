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
			switch (mem[p].hh.b0)
			{
				case 0:
				case 1:
				case 13:
					if (mem[p].hh.b0 == 0)
						printesc('h');
					else 
						if (mem[p].hh.b0 == 1)
							printesc('v');
						else
							printesc(318); //unset
					print(319); //box(
					printscaled(mem[p+3].int_);
					printchar('+');
					printscaled(mem[p+2].int_);
					print(320); //)x
					printscaled(mem[p+1].int_);
					if (mem[p].hh.b0 == 13)
					{
						if (mem[p].hh.b1)
						{
							print(286); // (
							printint(mem[p].hh.b1+1);
							print(322); // columns)
						}
						if (mem[p+6].int_)
						{
							print(323); //, stretch 
							printglue(mem[p+6].int_, mem[p+5].hh.b1, 0);
						}
						if (mem[p+4].int_)
						{
							print(324); //, shrink 
							printglue(mem[p+4].int_, mem[p+5].hh.b0, 0);
						}
					}
					else
					{
						g = mem[p+6].gr;
						if (g && mem[p+5].hh.b0)
						{
							print(325); //, glue set 
							if (mem[p+5].hh.b0 == 2)
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
									printglue(20000*65536, mem[p+5].hh.b1, 0);
								}
								else
									printglue(round(65536*g), mem[p+5].hh.b1, 0);
						}
						if (mem[p+4].int_)
						{
							print(321); //, shifted 
							printscaled(mem[p+4].int_);
						}
					}
					strpool[poolptr++] = '.';
					shownodelist(mem[p+5].hh.rh);
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
					printint(mem[p].hh.b1);
					print(331); //, natural size 
					printscaled(mem[p+3].int_);
					print(332); //; split(
					printspec(mem[p+4].hh.rh, 0);
					printchar(',');
					printscaled(mem[p+2].int_);
					print(333); //); float cost 
					printint(mem[p+1].int_);
					strpool[poolptr++] = '.';
					shownodelist(mem[p+4].hh.lh);
					poolptr--;
					break;
				case 8:
					switch (mem[p].hh.b1)
					{
						case 0:
							printwritewhatsit(1284, p); //openout
							printchar('=');
							printfilename(mem[p+1].hh.rh, mem[p+2].hh.lh, mem[p+2].hh.rh);
							break;
						case 1:
							printwritewhatsit(594, p); //write
							printmark(mem[p+1].hh.rh);
							break;
						case 2: 
							printwritewhatsit(1285, p); //closeout
							break;
						case 3:
							printesc(1286); //special
							printmark(mem[p+1].hh.rh);
							break;
						case 4:
							printesc(1288); //setlanguage
							printint(mem[p+1].hh.rh);
							print(1291); // (hyphenmin 
							printint(mem[p+1].hh.b0);
							printchar(',');
							printint(mem[p+1].hh.b1);
							printchar(')');
							break;
						default: 
							print(1292); //whatsit?
					}
					break;
				case 10:
					if (mem[p].hh.b1 >= 100)
					{
						printesc(338); //
						if (mem[p].hh.b1 == 101)
							printchar('c');
						else 
							if (mem[p].hh.b1 == 102)
								printchar('x');
						print(339); //leaders 
						printspec(mem[p+1].hh.lh, 0);
						strpool[poolptr++] = '.';
						shownodelist(mem[p+1].hh.rh);
						poolptr--;
					}
					else
					{
						printesc(334); //glue
						if (mem[p].hh.b1)
						{
							printchar('(');
							if (mem[p].hh.b1 < 98)
								printskipparam(mem[p].hh.b1-1);
							else 
								if (mem[p].hh.b1 == 98)
								printesc(335); //nonscript
							else
								printesc(336); //mskip
							printchar(')');
						}
						if (mem[p].hh.b1 != 98)
						{
							printchar(' ');
							if (mem[p].hh.b1 < 98)
								printspec(mem[p+1].hh.lh, 0);
							else
								printspec(mem[p+1].hh.lh, 337); //mu
						}
					}
				case 11:
					if (mem[p].hh.b1 != 99)
					{
						printesc(340); //kern
						if (mem[p].hh.b1)
							printchar(' ');
						printscaled(mem[p+1].int_);
						if (mem[p].hh.b1 == 2)
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
					if (mem[p].hh.b1 == 0)
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
					if (mem[p].hh.b1 > 1)
						printchar('|');
					fontinshortdisplay = mem[p+1].hh.b0;
					shortdisplay(mem[p+1].hh.rh);
					if (mem[p].hh.b1%2)
						printchar('|');
					printchar(')');
					break;
				case 12:
					printesc(348); //penalty 
					printint(mem[p+1].int_);
					break;
				case 7:
					printesc(349); //discretionary
					if (mem[p].hh.b1 > 0)
					{
						print(350); // replacing 
						printint(mem[p].hh.b1);
					}
					strpool[poolptr++] = '.';
					shownodelist(mem[p+1].hh.lh);
					poolptr--;
					strpool[poolptr++] = '|';
					shownodelist(mem[p+1].hh.rh);
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
					printstyle(mem[p].hh.b1);
					break;
				case 15:
					printesc(525); //mathchoice
					strpool[poolptr++] = 'D';
					shownodelist(mem[p+1].hh.lh);
					poolptr--;
					strpool[poolptr++] = 'T';
					shownodelist(mem[p+1].hh.rh);
					poolptr--;
					strpool[poolptr++] = 'S';
					shownodelist(mem[p+2].hh.lh);
					poolptr--;
					strpool[poolptr++] = 's';
					shownodelist(mem[p+2].hh.rh);
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
					switch (mem[p].hh.b0)
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
					if (mem[p].hh.b1)
						if (mem[p].hh.b1 == 1)
							printesc(877); //limits
						else
							printesc(878); //nolimits
					if (mem[p].hh.b0 < 30)
					printsubsidiarydata(p+1, '.');
					printsubsidiarydata(p+2, '^');
					printsubsidiarydata(p+3, '_');
					break;
				case 25:
					printesc(879); //fraction, thickness 
					if (mem[p+1].int_ == 1073741824)
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
		p = mem[p].hh.rh;
	}
}
