#include "scanint.h"
#include "getxtoken.h"
#include "gettoken.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "backinput.h"
#include "scansomethinginternal.h"
#include "error.h"

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
		if (curtok == other_char*0x01'00+'-')
		{
			negative = !negative;
			curtok = other_char*0x01'00+'+';
		}
	} while (curtok == other_char*0x01'00+'+');
	if (curtok == other_char*0x01'00+'`')
	{
		gettoken();
		if (curtok < cs_token_flag)
		{
			curval = curchr;
			if (curcmd <= right_brace)
				if (curcmd == right_brace)
					alignstate++;
				else
					alignstate--;
		}
		else 
			if (curtok < 0x11'00) // cmd < 17
				curval = curtok-0x10'00;
			else
				curval = curtok-0x11'00;
		if (curval > 0xFF)
		{
			printnl(262); //! 
			print(698); //Improper alphabetic constant
			helpptr = 2;
			helpline[1] = 699; //A one-character control sequence belongs after a ` mark.
			helpline[0] = 700; //So I'm essentially inserting \0 here.
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
			auto m = 214748364;
			if (curtok == 3111) //other_char+'\''
			{
				radix = 8;
				m = 0x10'00'00'00;
				getxtoken();
			}
			else 
				if (curtok == 3106) //other_char+'\"'
				{
					radix = 16;
					m = 0x08'00'00'00;
					getxtoken();
				};
			bool vacuous = true;
			curval = 0;
			while (true)
			{
				int d;
				if (curtok < 0x0C'00+'0'+radix && curtok >= 0x0C'00+'0' && curtok <= 0x0C'00+'9')
					d = curtok-0x0C'00-'0'; // 0xc00 = other_char
				else 
					if (radix == 16)
						if (curtok <= 0x0B'00+'F' && curtok >= 0x0B'00+'A') //oxb00 = letter
							d = curtok-0x0B'00-'A'+10;
						else 
							if (curtok <= 0x0C'00+'F' && curtok >= 0x0C'00+'A') // 0xc00 = other_char
								d = curtok-0x0C'00-'A'+10;
							else
								break;
					else
						break;
				vacuous = false;
				if (curval >= m && (curval > m || d > 7 || radix != 10))
				{
					if (OKsofar)
					{
						printnl(262); //! 
						print(701); //Number too big
						helpptr = 2;
						helpline[1] = 702; //I can only go up to 2147483647='17777777777="7FFFFFFF,
						helpline[0] = 703; //so I'm using that number instead of yours.
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
				printnl(262); //! 
				print(664); //Missing number, treated as zero
				helpptr = 3;
				helpline[2] = 665; //A number should have been here; I inserted `0'.
				helpline[1] = 666; //(If you can't figure out why I needed to see a number,
				helpline[0] = 667; //look up `weird error' in the index to The TeXbook.)
				backerror();
			}
			else 
				if (curcmd != spacer)
					backinput();
		}
	if (negative)
		curval = -curval;
}
