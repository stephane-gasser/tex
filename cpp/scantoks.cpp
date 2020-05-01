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
	halfword t = 3120;
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
				info(q) = 3584;
				p = q;
				if (curcmd == 2)
				{
					if (interaction == 3)
						printnl(262); //! 
					print(657); //Missing { inserted
					alignstate++;
					helpptr = 2;
					helpline[1] = 742; //Where was the left brace? You said something like `\def\a}',
					helpline[0] = 743; //which I'm going to interpret as `\def\a{}'.
					error();
					l40 = true;
					break;
				}
				break;
			}
			if (curcmd == 6)
			{
				auto s = 3328+curchr;
				gettoken();
				if (curcmd == 1)
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
					info(q) = 3584;
					p = q;
					break;
				}
				if (t == 3129)
				{
					if (interaction == 3)
						printnl(262); //! 
					print(744); //You already have nine parameters
					helpptr = 1;
					helpline[0] = 745; //I'm going to ignore the # sign you just used.
					error();
				}
				else
				{
					t++;
					if (curtok != t)
					{
						if (interaction == 3)
							printnl(262); //! 
						print(746); //Parameters must be numbered consecutively
						helpptr = 2;
						helpline[1] = 747; //I've inserted the digit you should have used after the #.
						helpline[0] = 748; //Type `1' to delete what you did use.
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
				if (curcmd <= 100)
					break;
				if (curcmd != 109)
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
		if (curtok < 768)
			if (curcmd < 2)
				unbalance++;
			else
			{
				unbalance--;
				if (unbalance == 0)
					break;
			}
		else 
			if (curcmd == 6)
				if (macrodef)
				{
					auto s = curtok;
					if (xpand)
						getxtoken();
					else
						gettoken();
					if (curcmd != 6)
						if (curtok <= 3120 || curtok > t)
						{
							if (interaction == 3)
								printnl(262); //! 
							print(749); //Illegal parameter number in definition of 
							sprintcs(warningindex);
							helpptr = 3;
							helpline[2] = 750; //You meant to type ## instead of #, right?
							helpline[1] = 751; //Or maybe a } was forgotten somewhere earlier, and things
							helpline[0] = 752; //are all screwed up? I'm going to assume that you meant ##.
							backerror();
							curtok = s;
						}
						else
							curtok = 1232+curchr;
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
