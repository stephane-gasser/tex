#include "expand.h"
#include "showcurcmdchr.h"
#include "begintokenlist.h"
#include "gettoken.h"
#include "backinput.h"
#include "getavail.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "backerror.h"
#include "overflow.h"
#include "idlookup.h"
#include "flushlist.h"
#include "eqdefine.h"
#include "convtoks.h"
#include "insthetoks.h"
#include "conditional.h"
#include "insertrelax.h"
#include "printcmdchr.h"
#include "error.h"
#include "passtext.h"
#include "freenode.h"
#include "startinput.h"
#include "macrocall.h"
#include "texte.h"

void expand(void)
{
	int cvbackup = curval;
	smallnumber cvlbackup = curvallevel;
	smallnumber radixbackup = radix;
	smallnumber cobackup = curorder;
	halfword backupbackup = link(backup_head);
	if (curcmd < call)
	{
		if (int_par(tracing_commands_code) > 1)
			showcurcmdchr();
		halfword t;
		smallnumber savescannerstatus;
		halfword p, q, r;
		int j;
		switch (curcmd)
		{
			case top_bot_mark:
				if (curmark[curchr])
					begintokenlist(curmark[curchr], 14);
				break;
			case expand_after:
				gettoken();
				t = curtok;
				gettoken();
				if (curcmd > max_command)
					expand();
				else
					backinput();
				curtok = t;
				backinput();
				break;
			case no_expand:
				savescannerstatus = scannerstatus;
				scannerstatus = 0;
				gettoken();
				scannerstatus = savescannerstatus;
				t = curtok;
				backinput();
				if (t >= cs_token_flag)
				{
					p = getavail();
					info(p) = frozen_dont_expand+cs_token_flag;
					link(p) = curinput.locfield;
					curinput.startfield = p;
					curinput.locfield = p;
				}
				break;
			case cs_name:
				r = getavail();
				p = r;
				do
				{
					getxtoken();
					if (curcs == 0)
					{
						q = getavail();
						link(p) = q;
						info(q) = curtok;
						p = q;
					}
				} while (curcs == 0);
				if (curcmd != 67)
				{
					printnl("! ");
					print("Missing ");
					printesc("endcsname");
					print(" inserted");
					helpptr = 2;
					helpline[1] = txt("The control sequence marked <to be read again> should");
					helpline[0] = txt("not appear between \\csname and \\endcsname.");
					backerror();
				}
				j = First;
				p = link(r);
				while (p)
				{
					if (j >= maxbufstack)
					{
						maxbufstack = j+1;
						if (maxbufstack == bufsize)
							overflow("buffer size", bufsize);
					};
					buffer[j++] = info(p)%0x1'00;
					p = link(p);
				};
				if (j > First+1)
				{
					nonewcontrolsequence = false;
					curcs = idlookup(First, j-First);
					nonewcontrolsequence = true;
				}
				else 
					if (j == First)
					curcs = 513;
				else
					curcs = 257+buffer[First];
				flushlist(r);
				if (eq_type(curcs) == undefined_cs)
					eqdefine(curcs, 0, 256);
				curtok = curcs+cs_token_flag;
				backinput();
				break;
			case convert: 
				convtoks();
				break;
			case the: 
				insthetoks();
				break;
			case if_test: 
				conditional();
				break;
			case fi_or_else:
				if (curchr > iflimit)
					if (iflimit = 1)
						insertrelax();
					else
					{
						printnl("! ");
						print("Extra ");
						printcmdchr(fi_or_else, curchr); 
						{
							helpptr = 1;
							helpline[0] = txt("I'm ignoring this; it doesn't match any \\if.");
						}
						error();
					}
				else
				{
					while (curchr != 2)
						passtext();
					p = condptr;
					ifline = if_line_field(p);
					curif = subtype(p);
					iflimit = type(p);
					condptr = link(p);
					freenode(p, 2);
				}
				break;
			case input:
				if (curchr > 0)
					forceeof = true;
				else 
					if (nameinprogress)
						insertrelax();
					else
						startinput();
				break;
			default:
				printnl("! ");
				print("Undefined control sequence");
				helpptr = 5;
				helpline[4] = txt("The control sequence at the end of the top line");
				helpline[3] = txt("of your error message was never \\def'ed. If you have");
				helpline[2] = txt("misspelled it (e.g., `\\hobx'), type `I' and the correct");
				helpline[1] = txt("spelling (e.g., `I\\hbox'). Otherwise just continue,");
				helpline[0] = txt("and I'll forget about whatever was undefined.");
				error();
		}
	}
	else 
		if (curcmd < end_template)
			macrocall();
		else
		{
			curtok = frozen_endv+cs_token_flag; 
			backinput();
		}
	curval = cvbackup;
	curvallevel = cvlbackup;
	radix = radixbackup;
	curorder = cobackup;
	link(backup_head) = backupbackup;
}
