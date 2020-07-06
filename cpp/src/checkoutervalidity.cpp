#include "checkoutervalidity.h"
#include "impression.h"
#include "erreur.h"
#include "getavail.h"
#include "begintokenlist.h"
#include "runaway.h"
#include "texte.h"

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
					error(curcs ? "Forbidden control sequence found" : "File ended while scanning definition of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.");
					info(p) = right_brace_token+'}';
					break;
				case matching:
					error(curcs ? "Forbidden control sequence found" : "File ended while scanning use of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.");
					info(p) = partoken;
					longstate = outer_call;
					break;
				case aligning:
					error(curcs ? "Forbidden control sequence found" : "File ended while scanning preamble of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.");
					info(p) = right_brace_token+'}';
					q = p;
					p = getavail();
					link(p) = q;
					info(p) = frozen_cr+cs_token_flag;
					alignstate = -1000000;
					break;
				case absorbing:
					error(curcs ? "Forbidden control sequence found" : "File ended while scanning text of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.");
					info(p) = right_brace_token+'}';
			}
			ins_list(p);
		}
		else
		{
			inserror("Incomplete "+cmdchr(if_test, curif)+"; all text was ignored after line "+std::to_string(skipline), std::string(curcs ? "A forbidden control sequence occurred in skipped text." : "The file ended while I was skipping conditional text.")+"This kind of error happens when you say `\\if...' and forget\nthe matching `\\fi'. I've inserted a `\\fi'; this might work.");
			curtok = frozen_fi+cs_token_flag;
		}
		curcs = 0;
		deletionsallowed = true;
	}
}
