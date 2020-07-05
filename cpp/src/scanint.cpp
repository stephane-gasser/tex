#include "scanint.h"
#include "getxtoken.h"
#include "gettoken.h"
#include "impression.h"
#include "backinput.h"
#include "scansomethinginternal.h"
#include "erreur.h"
#include "texte.h"

static void erreurScanint1(void)
{
	print_err("Improper alphabetic constant");
	helpptr = 2;
	helpline[1] = "A one-character control sequence belongs after a ` mark.";
	helpline[0] = "So I'm essentially inserting \\0 here.";
	backerror();
}

static void erreurScanint2(void)
{
	print_err("Number too big");
	helpptr = 2;
	helpline[1] = "I can only go up to 2147483647='17777777777=\"7FFFFFFF,";
	helpline[0] = "so I'm using that number instead of yours.";
	error();
}

static void erreurScanint3(void)
{
	print_err("Missing number, treated as zero");
	helpptr = 3;
	helpline[2] = "A number should have been here; I inserted `0'.";
	helpline[1] = "(If you can't figure out why I needed to see a number,";
	helpline[0] = "look up `weird error' in the index to The TeXbook.)";
	backerror();
}

//! Sets \a curval to an integer.
//! The \a scan_int routine is used also to scan the integer part of a 
//! fraction; for example, the `3' in `3.14159' will be found by 
//! \a scan_int. The \a scan_dimen routine assumes that <em> cur_tok=point_token </em>
//! after the integer part of such a fraction has been scanned by \a scan_int, 
//! and that the decimal point has been backed up to be scanned again. 
void scanint(void)
{
	radix = 0;
	bool OKsofar = true; // has an error message been issued?
	bool negative = false; // should the answer be negated?
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
			erreurScanint1();
			curval = '0';
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
				int d; //the digit just scanned
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
				vacuous = false; // has no digits appeared?
				if (curval >= m && (curval > m || d > 7 || radix != 10))
				{
					if (OKsofar)
					{
						erreurScanint2();
						curval = infinity;
						OKsofar = false;
					}
				}
				else
					curval = curval*radix+d;
				getxtoken();
			}
			if (vacuous)
				erreurScanint3();
			else 
				if (curcmd != spacer)
					backinput();
		}
	if (negative)
		curval = -curval;
}
