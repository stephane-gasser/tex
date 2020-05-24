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
			print(" []");
		return;
	}
	int n = 0;
	while (p > memmin)
	{
		println();
		printcurrentstring();
		if (p > memend)
		{
			print("Bad link, display aborted.");
			return;
		}
		n++;
		if (n > breadthmax)
		{
			print("etc.");
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
						printesc("h");
					else 
						if (type(p) == vlist_node)
							printesc("v");
						else
							printesc("unset");
					print("box(");
					printscaled(height(p));
					printchar('+');
					printscaled(depth(p));
					print(")x");
					printscaled(width(p));
					if (type(p) == unset_node)
					{
						if (subtype(p))
						{
							print(" (");
							printint(subtype(p)+1);
							print(" columns)");
						}
						if (glue_stretch(p))
						{
							print(", stretch ");
							printglue(glue_stretch(p), glue_order(p), 0);
						}
						if (glue_shrink(p))
						{
							print(", shrink ");
							printglue(glue_shrink(p), glue_sign(p), 0);
						}
					}
					else
					{
						g = glue_set(p);
						if (g && glue_sign(p))
						{
							print(", glue set ");
							if (glue_sign(p) == shrinking)
								print("- ");
							if (!std::isfinite(glue_set(p)))
								print("?.?");
							else 
								if (abs(g) > 20000.0)
								{
									if (g > 0.0)
										printchar('>');
									else
										print("< -");
									printglue(20000*0x1'00'00, glue_order(p), 0);
								}
								else
									printglue(round(0x1'00'00*g), glue_order(p), 0);
						}
						if (shift_amount(p))
						{
							print(", shifted ");
							printscaled(shift_amount(p));
						}
					}
					strpool[poolptr++] = '.';
					shownodelist(list_ptr(p));
					poolptr--;
					break;
				case rule_node:
					printesc("rule(");
					printruledimen(width(p));
					printchar('+');
					printruledimen(depth(p));
					print(")x");
					printruledimen(width(p));
					break;
				case ins_node:
					printesc("insert");
					printint(subtype(p));
					print(", natural size ");
					printscaled(height(p));
					print("; split(");
					printspec(split_top_ptr(p), 0);
					printchar(',');
					printscaled(depth(p));
					print("); float cost ");
					printint(float_cost(p));
					strpool[poolptr++] = '.';
					shownodelist(ins_ptr(p));
					poolptr--;
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case 0:
							printwritewhatsit("openout", p);
							printchar('=');
							printfilename(link(p+1), info(p+2), link(p+2));
							break;
						case 1:
							printwritewhatsit("write", p);
							printmark(link(p+1));
							break;
						case 2: 
							printwritewhatsit("closeout", p); 
							break;
						case 3:
							printesc("special");
							printmark(link(p+1));
							break;
						case 4:
							printesc("setlanguage");
							printint(link(p+1));
							print(" (hyphenmin"); 
							printint(type(p+1));
							printchar(',');
							printint(subtype(p+1));
							printchar(')');
							break;
						default: 
							print("whatsit?");
					}
					break;
				case glue_node:
					if (subtype(p) >= 100)
					{
						printesc("");
						if (subtype(p) == 101)
							printchar('c');
						else 
							if (subtype(p) == 102)
								printchar('x');
						print("leaders ");
						printspec(info(p+1), 0);
						strpool[poolptr++] = '.';
						shownodelist(link(p+1));
						poolptr--;
					}
					else
					{
						printesc("glue");
						if (subtype(p))
						{
							printchar('(');
							if (subtype(p) < 98)
								printskipparam(subtype(p)-1);
							else 
								if (subtype(p) == 98)
								printesc("nonscript");
							else
								printesc("mskip");
							printchar(')');
						}
						if (subtype(p) != 98)
						{
							printchar(' ');
							if (subtype(p) < 98)
								printspec(info(p+1), 0);
							else
								printspec(info(p+1), "mu");
						}
					}
				case kern_node:
					if (subtype(p) != 99)
					{
						printesc("kern");
						if (subtype(p))
							printchar(' ');
						printscaled(width(p));
						if (subtype(p) == 2)
							print(" (for accent)");
					}
					else
					{
						printesc("mkern");
						printscaled(width(p));
						print("mu");
					}
					break;
				case math_node:
					printesc("math");
					if (subtype(p) == 0)
						print("on");
					else
						print("off");
					if (width(p))
					{
						print(", surrounded ");
						printscaled(width(p));
					}
					break;
				case ligature_node:
					printfontandchar(p+1);
					print(" (ligature ");
					if (subtype(p) > 1)
						printchar('|');
					fontinshortdisplay = type(p+1);
					shortdisplay(link(p+1));
					if (subtype(p)%2)
						printchar('|');
					printchar(')');
					break;
				case penalty_node:
					printesc("penalty ");
					printint(penalty(p));
					break;
				case disc_node:
					printesc("discretionary");
					if (subtype(p) > 0)
					{
						print(" replacing ");
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
					printesc("mark");
					printmark(mark_ptr(p));
					break;
				case adjust_node:
					printesc("vadjust");
					strpool[poolptr++] = '.';
					shownodelist(adjust_ptr(p));
					poolptr--;
					break;
				case style_node: 
					printstyle(subtype(p));
					break;
				case choice_node:
					printesc("mathchoice");
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
							printesc("mathord");
							break;
						case op_noad: 
							printesc("mathop");
							break;
						case bin_noad: 
							printesc("mathbin");
							break;
						case rel_noad: 
							printesc("mathrel");
							break;
						case open_noad: 
							printesc("mathopen");
							break;
						case close_noad: 
							printesc("mathclose");
							break;
						case punct_noad: 
							printesc("mathpunct");
							break;
						case inner_noad: 
							printesc("mathinner");
							break;
						case over_noad: 
							printesc("overline");
							break;
						case under_noad: 
							printesc("underline");
							break;
						case vcenter_noad: 
							printesc("vcenter");
							break;
						case radical_noad:
							printesc("radical");
							printdelimiter(left_delimiter(4));
							break;
						case accent_noad:
							printesc("accent");
							printfamandchar(accent_chr(p));
							break;
						case left_noad:
							printesc("left");
							printdelimiter(delimiter(p));
							break;
						case right_noad:
							printesc("right");
							printdelimiter(delimiter(p));
					}
					if (subtype(p))
						if (subtype(p) == limits)
							printesc("limits");
						else
							printesc("nolimits");
					if (type(p) < left_noad)
						printsubsidiarydata(nucleus(p), '.');
					printsubsidiarydata(supscr(p), '^');
					printsubsidiarydata(subscr(p), '_');
					break;
				case fraction_noad:
					printesc("fraction, thickness ");
					if (new_hlist(p) == default_code)
						print("= default");
					else
						printscaled(new_hlist(p));
					if (small_fam(left_delimiter(p))
					 || small_char(left_delimiter(p))
					 || large_fam(left_delimiter(p))
					 || large_char(left_delimiter(p)))
					{
						print(", left-delimiter ");
						printdelimiter(left_delimiter(p));
					}
					if (small_fam(right_delimiter(p))
					 || small_char(right_delimiter(p))
					 || large_fam(right_delimiter(p))
					 || large_char(right_delimiter(p)))
					{
						print(", right-delimiter ");
						printdelimiter(right_delimiter(p));
					}
					printsubsidiarydata(numerator(p), '\\');
					printsubsidiarydata(denominator(p), '/');
					break;
				default: 
					print("Unknown node type!");
			}
		p = link(p);
	}
}
