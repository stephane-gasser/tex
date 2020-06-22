#include "scanint.h"
#include "getxtoken.h"
#include "gettoken.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "backinput.h"
#include "scansomethinginternal.h"
#include "error.h"
#include "texte.h"

void scanint(void)
{
	radix = 0;
	bool OKsofar = true;
	bool negative = false;
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
	if (curtok == alpha_token)
	{
		gettoken();
		if (curtok < cs_token_flag)
		{
			curval = curchr;
			if (curcmd == right_brace)
				alignstate++;
			if (curcmd == left_brace)
				alignstate--;
		}
		else 
			curval = curtok-cs_token_flag-(curtok < cs_token_flag+single_base ? active_base : single_base);
		if (curval > 0xFF)
		{
			printnl("! ");
			print("Improper alphabetic constant");
			helpptr = 2;
			helpline[1] = "A one-character control sequence belongs after a ` mark.";
			helpline[0] = "So I'm essentially inserting \\0 here.";
			curval = '0';
			backerror();
		}
		else
		{
			getxtoken();
			if (curcmd != spacer)
				backinput();
		}
	}
	else 
		if (curcmd >= min_internal && curcmd <= max_internal)
			scansomethinginternal(0, false);
		else
		{
			radix = 10;
			auto m = 214748364; //0xC'CC'CC'CC
			if (curtok == octal_token) //other_char+'\''
			{
				radix = 8;
				m = 0x10'00'00'00;
				getxtoken();
			}
			else 
				if (curtok == hex_token) //other_char+'\"'
				{
					radix = 16;
					m = 0x8'00'00'00;
					getxtoken();
				};
			bool vacuous = true;
			curval = 0;
			while (true)
			{
				int d;
				if (curtok < zero_token+radix && curtok >= zero_token && curtok <= zero_token+9)
					d = curtok-zero_token;
				else 
					if (radix == 16)
						if (curtok <= A_token+5 && curtok >= A_token)
							d = curtok-A_token+10;
						else 
							if (curtok <= other_A_token+5 && curtok >= other_A_token)
								d = curtok-other_A_token+10;
							else
								break;
					else
						break;
				vacuous = false;
				if (curval >= m && (curval > m || d > 7 || radix != 10))
				{
					if (OKsofar)
					{
						printnl("! ");
						print("Number too big");
						helpptr = 2;
						helpline[1] = "I can only go up to 2147483647='17777777777=\"7FFFFFFF,";
						helpline[0] = "so I'm using that number instead of yours.";
						error();
						curval = infinity;
						OKsofar = false;
					}
				}
				else
					curval = curval*radix+d;
				getxtoken();
			}
			if (vacuous)
			{
				printnl("! ");
				print("Missing number, treated as zero");
				helpptr = 3;
				helpline[2] = "A number should have been here; I inserted `0'.";
				helpline[1] = "(If you can't figure out why I needed to see a number,";
				helpline[0] = "look up `weird error' in the index to The TeXbook.)";
				backerror();
			}
			else 
				if (curcmd != spacer)
					backinput();
		}
	if (negative)
		curval = -curval;
}
