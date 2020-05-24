#include "scantoks.h"
#include "getavail.h"
#include "gettoken.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "backerror.h"
#include "scanleftbrace.h"
#include "getnext.h"
#include "expand.h"
#include "thetoks.h"
#include "xtoken.h"
#include "getxtoken.h"
#include "sprintcs.h"
#include "texte.h"

halfword scantoks(bool macrodef, bool xpand)
{
	if (macrodef)
		scannerstatus = 2;
	else
		scannerstatus = 5;
	warningindex = curcs;
	defref = getavail();
	info(defref) = 0;
	auto p = defref;
	halfword hashbrace = 0;
	halfword t = other_char*0x01'FF+'0';
	bool l40 = false;
	if (macrodef)
	{
		while (true)
		{
			gettoken();
			if (curtok < 768)
			{
				auto q = getavail();
				link(p) = q;
				info(q) = 0x0E'00; //cmd=end_match/comment/stop ?
				p = q;
				if (curcmd == right_brace)
				{
					printnl("! ");
					print("Missing { inserted"); 
					alignstate++;
					helpptr = 2;
					helpline[1] = txt("Where was the left brace? You said something like `\\def\\a}',");
					helpline[0] = txt("which I'm going to interpret as `\\def\\a{}'.");
					error();
					l40 = true;
					break;
				}
				break;
			}
			if (curcmd == mac_param)
			{
				auto s = 0x0D'00+curchr; // cmd = active_char/par_end/match?
				gettoken();
				if (curcmd == left_brace)
				{
					hashbrace = curtok;
					{
						auto q = getavail();
						link(p) = q;
						info(q) = curtok;
						p = q;
					}
					auto q = getavail();
					link(p) = q;
					info(q) = 0x0E'00; //cmd=end_match/comment/stop ?
					p = q;
					break;
				}
				if (t == other_char*0x01'00+'9')
				{
					printnl("! ");
					print("You already have nine parameters");
					helpptr = 1;
					helpline[0] = txt("I'm going to ignore the # sign you just used.");
					error();
				}
				else
				{
					t++;
					if (curtok != t)
					{
						printnl("! "); 
						print("Parameters must be numbered consecutively");
						helpptr = 2;
						helpline[1] = txt("I've inserted the digit you should have used after the #.");
						helpline[0] = txt("Type `1' to delete what you did use.");
						backerror();
					};
					curtok = s;
				}
			}
			auto q = getavail();
			link(p) = q;
			info(q) = curtok;
			p = q;
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
		if (curtok < 768) // cmd <= right_brace
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
						if (curtok <= other_char*0x01'00+'0' || curtok > t) 
						{
							printnl("! ");
							print("Illegal parameter number in definition of "); 
							sprintcs(warningindex);
							helpptr = 3;
							helpline[2] = txt("You meant to type ## instead of #, right?");
							helpline[1] = txt("Or maybe a } was forgotten somewhere earlier, and things");
							helpline[0] = txt("are all screwed up? I'm going to assume that you meant ##.");
							backerror();
							curtok = s;
						}
						else
							curtok = out_param*0x01'00+curchr-'0';
				}
		auto q = getavail();
		link(p) = q;
		info(q) = curtok;
		p = q;
	}
	scannerstatus = 0;
	if (hashbrace)
	{
		auto q = getavail();
		link(p) = q;
		info(q) = hashbrace;
		p = q;
	}
	return p;
}
