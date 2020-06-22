#include "scandimen.h"
#include "getxtoken.h"
#include "scansomethinginternal.h"
#include "deleteglueref.h"
#include "muerror.h"
#include "scanint.h"
#include "backinput.h"
#include "gettoken.h"
#include "getavail.h"
#include "rounddecimals.h"
#include "scankeyword.h"
#include "printnl.h"
#include "print.h"
#include "xnoverd.h"
#include "multandadd.h"
#include "error.h"
#include "preparemag.h"
#include "xnoverd.h"
#include "texte.h"

void scandimen(bool mu, bool inf, bool shortcut)
{
	int f = 0;
	aritherror = false;
	curorder = 0;
	bool negative = false;
	while (true) // label 89
	{
		if (!shortcut)
		{
			negative = false;
			do
			{
				do
					getxtoken();
				while (curcmd == spacer);
				if (curtok == other_token+'-')
				{
					negative = !negative;
					curtok = other_token+'+';
				}
			} while (curtok == other_token+'+');
			if (curcmd >= min_internal && curcmd <= max_internal)
				if (mu)
				{
					scansomethinginternal(mu_val, false);
					if (curvallevel >= glue_val)
					{
						auto v = width(curval);
						deleteglueref(curval);
						curval = v;
					}
					if (curvallevel == mu_val)
						break;
					if (curvallevel != int_val)
						muerror();
				}
				else
				{
					scansomethinginternal(dimen_val, false);
					if (curvallevel == dimen_val)
						break;
				}
			else
			{
				backinput();
				if (curtok == continental_point_token)
					curtok = point_token; 
				if (curtok != point_token)
					scanint();
				else
				{
					radix = 10;
					curval = 0;
				}
				if (curtok == continental_point_token) 
					curtok = point_token; 
				if (radix == 10 && curtok == point_token) 
				{
					int k = 0;
					halfword p = 0;
					gettoken();
					while (true)
					{
						getxtoken();
						if (curtok > zero_token+9 || curtok < zero_token)
							break;
						if (k < 17)
						{
							auto q = getavail();
							link(q) = p;
							info(q) = curtok-zero_token;
							p = q;
							k++;
						}
					}
					for (int kk = k; k > 0; k--)
					{
						dig[kk-1] = info(p);
						auto q = p;
						p = link(p);
						free_avail(q);
					}
					f = rounddecimals(k);
					if (curcmd != spacer)
						backinput();
				}
			}
		}
		if (curval < 0)
		{
			negative = !negative;
			curval = -curval;
		}
		if (inf)
			if (scankeyword("fil"))
			{
				curorder = 1;
				while (scankeyword("l")) 
				if (curorder == 3)
				{
					printnl("! ");
					print("Illegal unit of measure ("); 
					print("replaced by filll)");
					helpptr = 1;
					helpline[0] = "I dddon't go any higher than filll.";
					error();
				}
				else
					curorder++;
				if (curval >= 0x40'00)
					aritherror = true;
				else
					curval = curval*0x01'00'00+f;
				getxtoken();
				if (curcmd != spacer)
					backinput();
				break;
			}
		auto savecurval = curval;
		do
			getxtoken();
		while (curcmd == spacer);
		if (curcmd < min_internal || curcmd > max_internal)
			backinput();
		else
		{
			if (mu)
			{
				scansomethinginternal(3, false);
				if (curvallevel >= 2)
				{
					auto v = width(curval);
					deleteglueref(curval);
					curval = v;
				}
				if (curvallevel != 3)
					muerror();
			}
			else
				scansomethinginternal(1, false);
			auto v = curval;
			curval = nx_plus_y(savecurval, v, xnoverd(v, f, 0x1'00'00));
			break;
		}
		if (!mu)
		{
			if (scankeyword("em"))
			{
				auto v = quad(cur_font());
				getxtoken();
				if (curcmd != spacer)
					backinput();
			}
			else 
				if (scankeyword("ex"))
				{
					auto v = x_height(cur_font());
					getxtoken();
					if (curcmd != spacer)
						backinput();
				}
		}
		if (mu)
		{
			if (!scankeyword("mu"))
			{
				printnl("! ");
				print("Illegal unit of measure ("); 
				print("mu inserted)"); 
				helpptr = 4;
				helpline[3] = "The unit of measurement in math glue must be mu.";
				helpline[2] = "To recover gracefully from this error, it's best to";
				helpline[1] = "delete the erroneous units; e.g., type `2' to delete";
				helpline[0] = "two letters. (See Chapter 27 of The TeXbook.)";
				error();
			}
			if (curval >= 0x40'00)
				aritherror = true;
			else
				curval = curval*0x01'00'00+f;
			getxtoken();
			if (curcmd != spacer)
				backinput();
			break;
		}
		if (scankeyword("true"))
		{
			preparemag();
			if (mag() != 1000)
			{
				curval = xnoverd(curval, 1000, mag());
				f = (1000*f+0x01'00'00*remainder_)/mag();
				curval += f/0x01'00'00;
				f %= 0x01'00'00;
			}
		}
		if (scankeyword("pt"))
		{
			if (curval >= 0x40'00)
				aritherror = true;
			else
				curval = curval*unity+f;
			getxtoken();
			if (curcmd != spacer)
				backinput();
			break;
		}
		int num, denom;
		auto set_conversion = [&num, &denom](int n, int d){ num = n; denom = d; };
		if (scankeyword("in"))
			set_conversion(7227, 100); // 1 inch = 72.27 pt
		else 
			if (scankeyword("pc"))
				set_conversion(12, 1); // 1 pica = 12 pt
			else 
				if (scankeyword("cm"))
					set_conversion(7227, 254); // 1 inch = 2.54 cm
				else 
					if (scankeyword("mm"))
						set_conversion(7227, 2540); // 1 cm = 10 mm
					else 
						if (scankeyword("bp"))
							set_conversion(7227, 7200); // 1 inch = 72 bp
						else 
							if (scankeyword("dd"))
								set_conversion(1238, 1157);
							else 
								if (scankeyword("cc"))
									set_conversion(14856, 1157);
								else 
									if (scankeyword("sp")) 
									{
										getxtoken();
										if (curcmd != spacer)
											backinput();
										break;
									}
									else
									{
										printnl("! "); 
										print("Illegal unit of measure ("); 
										print("pt inserted)");
										helpptr = 6;
										helpline[5] = "Dimensions can be in units of em, ex, in, pt, pc,";
										helpline[4] = "cm, mm, dd, cc, bp, or sp; but yours is a new one!";
										helpline[3] = "I'll assume that you meant to say pt, for printer's points.";
										helpline[2] = "Dimension too large";
										helpline[1] = "I can't work with sizes bigger than about 19 feet.";
										helpline[0] = "Continue and I'll use the largest value I can.";
										error();
										if (curval >= 0x40'00)
											aritherror = true;
										else
											curval = curval*unity+f;
										getxtoken();
										if (curcmd != spacer)
											backinput();
										break;
									}
		curval = xnoverd(curval, num, denom);
		f = (num*f+remainder_<<16)/denom;
		curval += f>>16;
		f %= 1<<16;
		if (curval >= 0x40'00)
			aritherror = true;
		else
			curval = curval*unity+f;
		getxtoken();
		if (curcmd != spacer)
			backinput();
		break;
	} 
	if (aritherror || abs(curval) >= 0x40'00'00'00)
	{
		printnl("! ");
		print("Dimension too large"); 
		helpptr = 2;
		helpline[1] = "I can't work with sizes bigger than about 19 feet.";
		helpline[0] = "Continue and I'll use the largest value I can.";
		error;
		curval = max_dimen;
		aritherror = false;
	}
	if (negative)
		curval = -curval;
}

void scan_normal_dimen(void)
{
	scandimen(false, false, false);
}
