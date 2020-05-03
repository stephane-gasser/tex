#include "checkoutervalidity.h"
#include "print.h"
#include "printcmdchr.h"
#include "printcs.h"
#include "printint.h"
#include "inserror.h"
#include "printnl.h"
#include "getavail.h"
#include "begintokenlist.h"
#include "sprintcs.h"
#include "runaway.h"
#include "error.h"

void checkoutervalidity(void)
{
	if (scannerstatus)
	{
		deletionsallowed = false;
		if (curcs)
		{
			if (curinput.statefield == 0 || curinput.namefield < 1 || curinput.namefield > 17)
			{
				auto p = getavail();
				info(p) = cs_token_flag+curcs;
				begintokenlist(p, 3);
			}
			curcmd = spacer;
			curchr = ' ';
		}
		if (scannerstatus > 1)
		{
			runaway();
			if (curcs == 0)
			{
				printnl(262); //! 
				print(604); //File ended
			}
			else
			{
				curcs = 0;
				printnl(262); //! 
				print(605); //Forbidden control sequence found
			}
			print(606); // while scanning 
			auto p = getavail();
			decltype(p) q;
			switch (scannerstatus)
			{
				case 2:
					print(570); //definition
					info(p) = right_brace*0x01'00+'}';
					break;
				case 3:
					print(612); //use
					info(p) = partoken;
					longstate = 113;
					break;
				case 4:
					print(572); //preamble
					info(p) = right_brace*0x01'00+'}';
					q = p;
					p = getavail();
					link(p) = q;
					info(p) = frozen_cr+cs_token_flag;
					alignstate = -1000000;
					break;
				case 5:
					print(573); //text
					info(p) = right_brace*0x01'00+'}';
			}
			begintokenlist(p, 4);
			print(607); // of 
			sprintcs(warningindex);
			{
				helpptr = 4;
				helpline[3] = 608; //I suspect you have forgotten a `}', causing me
				helpline[2] = 609; //to read past where you wanted me to stop.
				helpline[1] = 610; //I'll try to recover; but if the error is serious,
				helpline[0] = 611; //you'd better type `E' or `X' now and fix your file.
			}
			error();
		}
		else
		{
			printnl(262); //! 
			print(598); //Incomplete 
			printcmdchr(105, curif);
			print(599); //; all text was ignored after line 
			printint(skipline);
			helpptr = 3;
			helpline[2] = 600; //A forbidden control sequence occurred in skipped text.
			helpline[1] = 601; //This kind of error happens when you say `\if...' and forget
			helpline[0] = 602; //the matching `\fi'. I've inserted a `\fi'; this might work.
			if (curcs)
				curcs = 0;
			else
				helpline[2] = 603; //The file ended while I was skipping conditional text.
			curtok = frozen_fi+cs_token_flag;
			inserror();
		}
		deletionsallowed = true;
	}
}
