#include "checkoutervalidity.h"
#include "impression.h"
#include "erreur.h"
#include "getavail.h"
#include "begintokenlist.h"
#include "runaway.h"
#include "texte.h"

static void erreurCheckoutervalidity1(const std::string &s)
{
	print_err(curcs ? "Forbidden control sequence found" : "File ended while scanning "+s+" of "+scs(warningindex));
	helpptr = 4;
	helpline[3] = "I suspect you have forgotten a `}', causing me";
	helpline[2] = "to read past where you wanted me to stop.";
	helpline[1] = "I'll try to recover; but if the error is serious,";
	helpline[0] = "you'd better type `E' or `X' now and fix your file.";
	error();
}

static void erreurCheckoutervalidity2(void)
{
	print_err("Incomplete "+cmdchr(if_test, curif)+"; all text was ignored after line "+std::to_string(skipline));
	helpptr = 3;
	helpline[2] = curcs ? "A forbidden control sequence occurred in skipped text." : "The file ended while I was skipping conditional text.";
	helpline[1] = "This kind of error happens when you say `\\if...' and forget";
	helpline[0] = "the matching `\\fi'. I've inserted a `\\fi'; this might work.";
	inserror();
}

void checkoutervalidity(void)
{
	if (scannerstatus)
	{
		deletionsallowed = false;
		if (curcs)
		{
			if (state == token_list || txt(name) < 1 || txt(name) > 17)
			{
				auto p = getavail();
				info(p) = cs_token_flag+curcs;
				back_list(p);
			}
			curcmd = spacer;
			curchr = ' ';
		}
		if (scannerstatus > skipping)
		{
			runaway();
			auto p = getavail();
			decltype(p) q;
			switch (scannerstatus)
			{
				case defining:
					erreurCheckoutervalidity1("definition");
					info(p) = right_brace_token+'}';
					break;
				case matching:
					erreurCheckoutervalidity1("use");
					info(p) = partoken;
					longstate = outer_call;
					break;
				case aligning:
					erreurCheckoutervalidity1("preamble");
					info(p) = right_brace_token+'}';
					q = p;
					p = getavail();
					link(p) = q;
					info(p) = frozen_cr+cs_token_flag;
					alignstate = -1000000;
					break;
				case absorbing:
					erreurCheckoutervalidity1("text");
					info(p) = right_brace_token+'}';
			}
			ins_list(p);
		}
		else
		{
			erreurCheckoutervalidity2();
			curtok = frozen_fi+cs_token_flag;
		}
		curcs = 0;
		deletionsallowed = true;
	}
}
