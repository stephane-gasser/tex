#include "scantoks.h"
#include "getavail.h"
#include "gettoken.h"
#include "impression.h"
#include "erreur.h"
#include "scanleftbrace.h"
#include "getnext.h"
#include "expand.h"
#include "thetoks.h"
#include "xtoken.h"
#include "getxtoken.h"
#include "texte.h"

halfword scantoks(bool macrodef, bool xpand)
{
	scannerstatus = macrodef ? defining : absorbing;
	warningindex = curcs;
	defref = getavail();
	token_ref_count(defref) = 0;
	auto p = defref;
	halfword hashbrace = 0;
	halfword t = zero_token;
	bool l40 = false;
	if (macrodef)
	{
		while (true)
		{
			gettoken();
			if (curtok < right_brace_limit)
			{
				store_new_token(p, end_match_token);
				if (curcmd == right_brace)
				{
					error("Missing { inserted", "Where was the left brace? You said something like `\\def\\a}',\nwhich I'm going to interpret as `\\def\\a{}'.");
					alignstate++;
					l40 = true;
					break;
				}
				break;
			}
			if (curcmd == mac_param)
			{
				auto s = match_token+curchr;
				gettoken();
				if (curcmd == left_brace)
				{
					hashbrace = curtok;
					store_new_token(p, curtok);
					store_new_token(p, end_match_token);
					break;
				}
				if (t == zero_token+9)
					error("You already have nine parameters", "I'm going to ignore the # sign you just used.");
				else
				{
					t++;
					if (curtok != t)
						backerror("Parameters must be numbered consecutively", "I've inserted the digit you should have used after the #.\nType `1' to delete what you did use.");
					curtok = s;
				}
			}
			store_new_token(p, curtok);
		}
	}
	else
		scanleftbrace();
	halfword unbalance;
	if (!l40)
		unbalance = 1;
	while (!l40)
	{
		if (xpand)
		{
			while (true)
			{
				getnext();
				if (curcmd <= max_command)
					break;
				if (curcmd != the)
					expand();
				else
				{
					auto q = thetoks();
					if (link(temp_head))
					{
						link(p) = link(temp_head);
						p = q;
					}
				}
			};
			xtoken();
		}
		else
			gettoken();
		if (curtok < right_brace_limit) 
			if (curcmd < right_brace)
				unbalance++;
			else
			{
				unbalance--;
				if (unbalance == 0)
					break;
			}
		else 
			if (curcmd == mac_param)
				if (macrodef)
				{
					auto s = curtok;
					if (xpand)
						getxtoken();
					else
						gettoken();
					if (curcmd != mac_param)
						if (curtok <= zero_token || curtok > t) 
						{
							backerror("Illegal parameter number in definition of "+scs(warningindex), "You meant to type ## instead of #, right?\nOr maybe a } was forgotten somewhere earlier, and things\nare all screwed up? I'm going to assume that you meant ##.");
							curtok = s;
						}
						else
							curtok = out_param_token-'0'+curchr;
				}
		store_new_token(p, curtok);
	}
	scannerstatus = 0;
	if (hashbrace)
		store_new_token(p, hashbrace);
	return p;
}
