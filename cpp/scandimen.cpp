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
				if (curtok == other_char*0x01'00+'-')
				{
					negative = !negative;
					curtok = other_char*0x01'00+'+';
				}
			} while (curtok == other_char*0x01'00+'+');
			if (curcmd >= min_internal && curcmd <= max_internal)
				if (mu)
				{
					scansomethinginternal(3, false);
					if (curvallevel >= 2)
					{
						auto v = width(curval);
						deleteglueref(curval);
						curval = v;
					}
					if (curvallevel == 3)
						break;
					if (curvallevel)
						muerror();
				}
				else
				{
					scansomethinginternal(1, false);
					if (curvallevel == 1)
						break;
				}
			else
			{
				backinput();
				if (curtok == other_char*0x01'00+',')
					curtok = other_char*0x01'00+'.'; 
				if (curtok != other_char*0x01'00+'.')
					scanint();
				else
				{
					radix = 10;
					curval = 0;
				}
				if (curtok == other_char*0x01'00+',') 
					curtok = other_char*0x01'00+'.'; 
				if (radix == 10 && curtok == other_char*0x01'00+'.') 
				{
					int k = 0;
					halfword p = 0;
					gettoken();
					while (true)
					{
						getxtoken();
						if (curtok > other_char*0x01'00+'9' || curtok < other_char*0x01'00+'0')
							break;
						if (k < 17)
						{
							auto q = getavail();
							link(q) = p;
							info(q) = curtok-(other_char*0x01'00+'0');
							p = q;
							k++;
						}
					}
					for (int kk = k; k > 0; k--)
					{
						dig[kk-1] = info(p);
						auto q = p;
						p = link(p);
						link(q) = avail;
						avail = q;
					};
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
				while (scankeyword('l')) 
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
			curval = multandadd(savecurval, v, xnoverd(v, f, 0x01'00'00), max_dimen);
			break;
		}
		if (!mu)
		{
			if (scankeyword("em"))
			{
				auto v = param(quad_code, cur_font());
				getxtoken();
				if (curcmd != spacer)
					backinput();
			}
			else 
				if (scankeyword("ex"))
				{
					auto v = param(x_height_code, cur_font());
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
			if (int_par(mag_code) != 1000)
			{
				curval = xnoverd(curval, 1000, int_par(mag_code));
				f = (1000*f+0x01'00'00*remainder_)/int_par(mag_code);
				curval += f/0x01'00'00;
				f %= 0x01'00'00;
			}
		}
		if (scankeyword("pt"))
		{
			if (curval >= 0x40'00)
				aritherror = true;
			else
				curval = curval*0x01'00'00+f;
			getxtoken();
			if (curcmd != spacer)
				backinput();
			break;
		}
		int num, denom;
		if (scankeyword("in"))
		{
			num = 7227;
			denom = 100;
		}
		else 
			if (scankeyword("pc"))
			{
				num = 12;
				denom = 1;
			}
			else 
				if (scankeyword("cm"))
				{
					num = 7227;
					denom = 254;
				}
				else 
					if (scankeyword("mm"))
					{
						num = 7227;
						denom = 2540;
					}
					else 
						if (scankeyword("bp"))
						{
							num = 7227;
							denom = 7200;
						}
						else 
							if (scankeyword("dd"))
							{
								num = 1238;
								denom = 1157;
							}
							else 
								if (scankeyword("cc"))
								{
									num = 14856;
									denom = 1157;
								}
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
											curval = curval*0x01'00'00+f;
										getxtoken();
										if (curcmd != spacer)
											backinput();
										break;
									}
		curval = xnoverd(curval, num, denom);
		f = (num*f+0x01'00'00*remainder_)/denom;
		curval += f/0x01'00'00;
		f %= 0x01'00'00;
		if (curval >= 0x40'00)
			aritherror = true;
		else
			curval = curval*0x01'00'00+f;
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
