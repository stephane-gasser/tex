#include "prefixedcommand.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "printchar.h"
#include "backerror.h"
#include "printesc.h"
#include "error.h"
#include "getrtoken.h"
#include "geqdefine.h"
#include "scantoks.h"
#include "gettoken.h"
#include "eqdefine.h"
#include "scanoptionalequals.h"
#include "backinput.h"
#include "scancharnum.h"
#include "scanfifteenbitint.h"
#include "scaneightbitint.h"
#include "scanint.h"
#include "readtoks.h"
#include "scankeyword.h"
#include "getavail.h"
#include "eqworddefine.h"
#include "scandimen.h"
#include "scanglue.h"
#include "trapzeroglue.h"
#include "geqworddefine.h"
#include "scancharnum.h"
#include "scanfourbitint.h"
#include "scanfontident.h"
#include "printint.h"
#include "doregistercommand.h"
#include "scanbox.h"
#include "alteraux.h"
#include "alterprevgraf.h"
#include "alterpagesofar.h"
#include "alterboxdimen.h"
#include "alterinteger.h"
#include "getnode.h"
#include "newpatterns.h"
#include "newhyphexceptions.h"
#include "findfontdimen.h"
#include "newfont.h"
#include "newinteraction.h"
#include "confusion.h"

void prefixedcommand(void)
{
	smallnumber a;
	internalfontnumber f;
	halfword j;
	fontindex k;
	halfword p, q;
	int n;
	bool e;
	a = 0;
	while (curcmd == 93)
	{
		if ((a/curchr)%2 == 0)
			a += curchr;
		do
			getxtoken();
		while (curcmd == 10 || curcmd == 0);
		if (curcmd <= 70)
		{
			if (interaction == 3)
				printnl(262); //! 
			print(1178); //You can't use a prefix with `
			printcmdchr(curcmd, curchr);
			printchar('\''); 
			helpptr = 1;
			helpline[0] = 1179; //I'll pretend you didn't say \long or \outer or \global.
			backerror;
			return;
		}
	}
	if (curcmd != 97 && a%4)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(685); //You can't use `
		printesc(1170); //long
		print(1180); //' or `
		printesc(1171); //outer
		print(1181); //' with `
		printcmdchr(curcmd, curchr);
		printchar('\'');
		helpptr = 1;
		helpline[0] = 1182; //I'll pretend you didn't say \long or \outer here.
		error();
	}
	if (int_par(global_defs_code))
		if (int_par(global_defs_code) < 0)
		{
			if (a >= 4)
				a -= 4;
		}
		else 
			if (a < 4)
			a += 4;
	switch (curcmd)
	{
		case 87: 
			if (a >= 4)
				geqdefine(3934, 120, curchr);
			else
				eqdefine(3934, 120, curchr);
			break;
		case 97:
			if (curchr%2 & a < 4  && int_par(global_defs_code) >= 0)
				a += 4;
			e = curchr >= 2;
			getrtoken();
			p = curcs;
			q = scantoks(true, e);
			if (a >= 4)
				geqdefine(p, 111+a%4, defref);
			else
				eqdefine(p, 111+a%4, defref);
			break;
		case 94:
			n = curchr;
			getrtoken();
			p = curcs;
			if (n == 0)
			{
				do
					gettoken();
				while (curcmd == 10);
				if (curtok == 3133)
				{
					gettoken();
					if (curcmd == 10)
						gettoken();
				}
			}
			else
			{
				gettoken();
				q = curtok;
				gettoken();
				backinput();
				curtok = q;
				backinput;
			}
			if (curcmd >= 111)
				info(curchr)++;
			if (a >= 4)
				geqdefine(p, curcmd, curchr);
			else
				eqdefine(p, curcmd, curchr);
			break;
		case 95:
			n = curchr;
			getrtoken();
			p = curcs;
			if (a >= 4)
				geqdefine(p, 0, 256);
			else
				eqdefine(p, 0, 256);
			scanoptionalequals();
			switch (n)
			{
				case 0:
					scancharnum();
					if (a >= 4)
						geqdefine(p, 68, curval);
					else
						eqdefine(p, 68, curval);
					break;
				case 1:
					scanfifteenbitint();
					if (a >= 4)
						geqdefine(p, 69, curval);
					else
						eqdefine(p, 69, curval);
					break;
				default:
					scaneightbitint();
					switch (n)
					{
						case 2: 
							if (a >= 4)
								geqdefine(p, 73, 5318+curval);
							else
								eqdefine(p, 73, 5318+curval);
							break;
						case 3: 
							if (a >= 4)
								geqdefine(p, 74, 5851+curval);
							else
								eqdefine(p, 74, 5851+curval);
							break;
						case 4: 
							if (a >= 4)
								geqdefine(p, 75, 2900+curval);
							else
								eqdefine(p, 75, 2900+curval);
							break;
						case 5: 
							if (a >= 4)
								geqdefine(p, 76, 3156+curval);
							else
								eqdefine(p, 76, 3156+curval);
							break;
						case 6: 
							if (a >= 4)
								geqdefine(p, 72, 3422+curval);
							else
								eqdefine(p, 72, 3422+curval);
					}
			}
			break;
		case 96:
			scanint();
			n = curval;
			if (!scankeyword(841)) //to
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1072); //Missing `to' inserted
				helpptr = 2;
				helpline[1] = 1199; //You should have said `\read<number> to \cs'.
				helpline[0] = 1200; //I'm going to look for the \cs now.
				error();
			}
			getrtoken();
			p = curcs;
			readtoks(n, p);
			if (a >= 4)
				geqdefine(p, 111, curval);
			else
				eqdefine(p, 111, curval);
			break;
		case 71:
		case 72:
			q = curcs;
			if (curcmd == 71)
			{
				scaneightbitint();
				p = 3422+curval;
			}
			else
				p = curchr;
			scanoptionalequals();
			do
				getxtoken();
			while (curcmd == 10 || curcmd == 0);
			if (curcmd != 1)
			{
				if (curcmd == 71)
				{
					scaneightbitint();
					curcmd = 72;
					curchr = 3422+curval;
				}
				if (curcmd == 72)
				{
					q = equiv(curchr);
					if (q == 0)
						if (a >= 4)
							geqdefine(p, 101, 0);
						else
							eqdefine(p, 101, 0);
					else
					{
						info(q)++;
						if (a >= 4)
							geqdefine(p, 111, q);
						else
							eqdefine(p, 111, q);
					}
					break;
				}
			}
			backinput();
			curcs = q;
			q = scantoks(false, false);
			if (link(defref) == 0)
			{
				if (a >= 4)
					geqdefine(p, 101, 0);
				else
					eqdefine(p, 101, 0);
				link(defref) = avail;
				avail = defref;
			}
			else
			{
				if (p == 3413)
				{
					link(q) = getavail();
					q = link(q);
					info(q) = 637;
					q = getavail();
					info(q) = 379;
					link(q) = link(defref);
					link(defref) = q;
				}
				if (a >= 4)
					geqdefine(p, 111, defref);
				else
					eqdefine(p, 111, defref);
			}
			break;
		case 73:
			p = curchr;
			scanoptionalequals();
			scanint();
			if (a >= 4)
				geqworddefine(p, curval);
			else
				eqworddefine(p, curval);
			break;
		case 74:
			p = curchr;
			scanoptionalequals();
			scandimen(false, false, false);
			if (a >= 4)
				geqworddefine(p, curval);
			else
				eqworddefine(p, curval);
			break;
		case 75:
		case 76:
			p = curchr;
			n = curcmd;
			scanoptionalequals();
			if (n == 76)
				scanglue(3);
			else
				scanglue(2);
			trapzeroglue();
			if (a >= 4)
				geqdefine(p, 117, curval);
			else
				eqdefine(p, 117, curval);
			break;
		case 85:
			if (curchr == 3983)
				n = 15;
			else 
				if (curchr == 5007)
					n = 32768;
				else 
					if (curchr == 4751)
						n = 32767;
					else 
						if (curchr == 5574)
							n = 16777215;
						else
						n = 255;
			p = curchr;
			scancharnum();
			p += curval;
			scanoptionalequals();
			scanint();
			if ((curval < 0 && p < 5574) || curval > n)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1201); //Invalid code (
				printint(curval);
				if (p < 5574)
					print(1202); //), should be in the range 0..
				else
					print(1203); //), should be at most 
				printint(n);
				helpptr = 1;
				helpline[0] = 1204; //I'm going to use 0 instead of that illegal code value.
				error;
				curval = 0;
			}
			if (p < 5007)
				if (a >= 4)
					geqdefine(p, 120, curval);
				else
					eqdefine(p, 120, curval);
			else 
				if (p < 5574)
					if (a >= 4)
						geqdefine(p, 120, curval);
					else
						eqdefine(p, 120, curval);
				else 
					if (a >= 4)
						geqworddefine(p, curval);
					else
						eqworddefine(p, curval);
			break;
		case 86:
			p = curchr;
			scanfourbitint();
			p += curval;
			scanoptionalequals();
			scanfontident();
			if (a >= 4)
				geqdefine(p, 120, curval);
			else
				eqdefine(p, 120, curval);
			break;
		case 89:
		case 90:
		case 91:
		case 92: 
			doregistercommand(a);
			break;
		case 98:
			scaneightbitint();
			if (a >= 4)
				n = 256+curval;
			else
				n = curval;
			scanoptionalequals();
			if (setboxallowed)
				scanbox(1073741824+n);
			else
			{
				if (interaction == 3)
					printnl(262); //! 
				print(680); //Improper 
				printesc(536); //setbox
				helpptr = 2;
				helpline[1] = 1210; //Sorry, \setbox is not allowed after \halign in a display,
				helpline[0] = 1211; //or between \accent and an accented character.
				error();
			}
			break;
		case 79: 
			alteraux();
			break;
		case 80: 
			alterprevgraf();
			break;
		case 81: 
			alterpagesofar();
			break;
		case 82: 
			alterinteger();
			break;
		case 83: 
			alterboxdimen();
			break;
		case 84:
			scanoptionalequals();
			scanint();
			n = curval;
			if (n <= 0)
				p = 0;
			else
			{
				p = getnode(2*n+1);
				info(p) = n;
				for (j = 1; j <= n; j++)
				{
					scandimen(false, false, false);
					mem[p+2*j-1].int_ = curval;
					scandimen(false, false, false);
					mem[p+2*j].int_ = curval;
				}
			}
			if (a >= 4)
				geqdefine(3412, 118, p);
			else
				eqdefine(3412, 118, p);
			break;
		case 99: 
			if (curchr == 1)
				newpatterns();
			else
				newhyphexceptions();
			break;
		case 77:
			findfontdimen(true);
			k = curval;
			scanoptionalequals();
			scandimen(false, false, false);
			fontinfo[k].int_ = curval;
			break;
		case 78:
			n = curchr;
			scanfontident();
			f = curval;
			scanoptionalequals();
			scanint();
			if (n == 0)
				hyphenchar[f] = curval;
			else
				skewchar[f] = curval;
			break;
		case 88: 
			newfont(a);
			break;
		case 100: 
			newinteraction();
			break;
		default: 
			confusion(1177); //prefix
	}
	if (aftertoken)
	{
		curtok = aftertoken;
		backinput();
		aftertoken = 0;
	}
}
