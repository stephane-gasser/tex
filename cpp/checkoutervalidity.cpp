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
#include "texte.h"

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
				printnl("! ");
				print("File ended");
			}
			else
			{
				curcs = 0;
				printnl("! ");
				print("Forbidden control sequence found");
			}
			print(" while scanning ");
			auto p = getavail();
			decltype(p) q;
			switch (scannerstatus)
			{
				case 2:
					print("definition");
					info(p) = right_brace*0x01'00+'}';
					break;
				case 3:
					print("use");
					info(p) = partoken;
					longstate = outer_call;
					break;
				case 4:
					print("preamble");
					info(p) = right_brace*0x01'00+'}';
					q = p;
					p = getavail();
					link(p) = q;
					info(p) = frozen_cr+cs_token_flag;
					alignstate = -1000000;
					break;
				case 5:
					print("text");
					info(p) = right_brace*0x01'00+'}';
			}
			begintokenlist(p, 4);
			print(" of ");
			sprintcs(warningindex);
			{
				helpptr = 4;
				helpline[3] = "I suspect you have forgotten a `}', causing me";
				helpline[2] = "to read past where you wanted me to stop.";
				helpline[1] = "I'll try to recover; but if the error is serious,";
				helpline[0] = "you'd better type `E' or `X' now and fix your file.";
			}
			error();
		}
		else
		{
			printnl("! ");
			print("Incomplete ");
			printcmdchr(if_test, curif);
			print("; all text was ignored after line ");
			printint(skipline);
			helpptr = 3;
			helpline[2] = "A forbidden control sequence occurred in skipped text.";
			helpline[1] = "This kind of error happens when you say `\\if...' and forget";
			helpline[0] = "the matching `\\fi'. I've inserted a `\\fi'; this might work.";
			if (curcs)
				curcs = 0;
			else
				helpline[2] = "The file ended while I was skipping conditional text.";
			curtok = frozen_fi+cs_token_flag;
			inserror();
		}
		deletionsallowed = true;
	}
}
