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
				case hlist_node:
				case vlist_node:
				case unset_node:
					if (type(p) == hlist_node)
						printesc('h');
					else 
						if (type(p) == vlist_node)
							printesc('v');
						else
							printesc(318); //unset
					print(319); //box(
					printscaled(height(p));
					printchar('+');
					printscaled(depth(p));
					print(320); //)x
					printscaled(width(p));
					if (type(p) == unset_node)
					{
						if (subtype(p))
						{
							print(286); // (
							printint(subtype(p)+1);
							print(322); // columns)
						}
						if (glue_stretch(p))
						{
							print(323); //, stretch 
							printglue(glue_stretch(p), glue_order(p), 0);
						}
						if (glue_shrink(p))
						{
							print(324); //, shrink 
							printglue(glue_shrink(p), glue_sign(p), 0);
						}
					}
					else
					{
						g = glue_set(p);
						if (g && glue_sign(p))
						{
							print(325); //, glue set 
							if (glue_sign(p) == shrinking)
								print(326); //- 
							if (!std::isfinite(glue_set(p)))
								print(327); //?.?
							else 
								if (abs(g) > 20000.0)
								{
									if (g > 0.0)
										printchar('>');
									else
										print(328); //< -
									printglue(20000*0x1'00'00, glue_order(p), 0);
								}
								else
									printglue(round(0x1'00'00*g), glue_order(p), 0);
						}
						if (shift_amount(p))
						{
							print(321); //, shifted 
							printscaled(shift_amount(p));
						}
					}
					strpool[poolptr++] = '.';
					shownodelist(list_ptr(p));
					poolptr--;
					break;
				case rule_node:
					printesc(329); //rule(
					printruledimen(width(p));
					printchar('+');
					printruledimen(depth(p));
					print(320); //)x
					printruledimen(width(p));
					break;
				case ins_node:
					printesc(330); //insert
					printint(subtype(p));
					print(331); //, natural size 
					printscaled(height(p));
					print(332); //; split(
					printspec(split_top_ptr(p), 0);
					printchar(',');
					printscaled(depth(p));
					print(333); //); float cost 
					printint(float_cost(p));
					strpool[poolptr++] = '.';
					shownodelist(ins_ptr(p));
					poolptr--;
					break;
				case whatsit_node:
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
				case glue_node:
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
				case kern_node:
					if (subtype(p) != 99)
					{
						printesc(340); //kern
						if (subtype(p))
							printchar(' ');
						printscaled(width(p));
						if (subtype(p) == 2)
							print(341); // (for accent)
					}
					else
					{
						printesc(342); //mkern
						printscaled(width(p));
						print(337); //mu
					}
					break;
				case math_node:
					printesc(343); //math
					if (subtype(p) == 0)
						print(344); //on
					else
						print(345); //off
					if (width(p))
					{
						print(346); //, surrounded 
						printscaled(width(p));
					}
					break;
				case ligature_node:
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
				case penalty_node:
					printesc(348); //penalty 
					printint(penalty(p));
					break;
				case disc_node:
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
				case mark_node:
					printesc(351); //mark
					printmark(mark_ptr(p));
					break;
				case adjust_node:
					printesc(352); //vadjust
					strpool[poolptr++] = '.';
					shownodelist(adjust_ptr(p));
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
				case ord_noad:
				case op_noad:
				case bin_noad:
				case rel_noad:
				case open_noad:
				case close_noad:
				case punct_noad:
				case inner_noad:
				case radical_noad:
				case over_noad:
				case under_noad:
				case vcenter_noad:
				case accent_noad:
				case left_noad:
				case right_noad:
					switch (type(p))
					{
						case ord_noad: 
							printesc(865); //mathord
							break;
						case op_noad: 
							printesc(866); //mathop
							break;
						case bin_noad: 
							printesc(867); //mathbin
							break;
						case rel_noad: 
							printesc(868); //mathrel
							break;
						case open_noad: 
							printesc(869); //mathopen
							break;
						case close_noad: 
							printesc(870); //mathclose
							break;
						case punct_noad: 
							printesc(871); //mathpunct
							break;
						case inner_noad: 
							printesc(872); //mathinner
							break;
						case over_noad: 
							printesc(873); //overline
							break;
						case under_noad: 
							printesc(874); //underline
							break;
						case vcenter_noad: 
							printesc(539); //vcenter
							break;
						case radical_noad:
							printesc(533); //radical
							printdelimiter(left_delimiter(4));
							break;
						case accent_noad:
							printesc(508); //accent
							printfamandchar(accent_chr(p));
							break;
						case left_noad:
							printesc(875); //left
							printdelimiter(delimiter(p));
							break;
						case right_noad:
							printesc(876); //right
							printdelimiter(delimiter(p));
					}
					if (subtype(p))
						if (subtype(p) == limits)
							printesc(877); //limits
						else
							printesc(878); //nolimits
					if (type(p) < left_noad)
						printsubsidiarydata(nucleus(p), '.');
					printsubsidiarydata(supscr(p), '^');
					printsubsidiarydata(subscr(p), '_');
					break;
				case fraction_noad:
					printesc(879); //fraction, thickness 
					if (new_hlist(p) == default_code)
						print(880); //= default
					else
						printscaled(new_hlist(p));
					if (small_fam(left_delimiter(p))
					 || small_char(left_delimiter(p))
					 || large_fam(left_delimiter(p))
					 || large_char(left_delimiter(p)))
					{
						print(881); //, left-delimiter 
						printdelimiter(left_delimiter(p));
					}
					if (small_fam(right_delimiter(p))
					 || small_char(right_delimiter(p))
					 || large_fam(right_delimiter(p))
					 || large_char(right_delimiter(p)))
					{
						print(882); //, right-delimiter 
						printdelimiter(right_delimiter(p));
					}
					printsubsidiarydata(numerator(p), '\\');
					printsubsidiarydata(denominator(p), '/');
					break;
				default: 
					print(317); //Unknown node type!
			}
		p = link(p);
	}
}
