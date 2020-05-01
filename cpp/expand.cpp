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

void expand(void)
/*var
  t: halfword;
  p, q, r: halfword;
  j: 0..bufsize;
  savescannerstatus: smallnumber;*/
{
	int cvbackup = curval;
	smallnumber cvlbackup = curvallevel;
	smallnumber radixbackup = radix;
	smallnumber cobackup = curorder;
	halfword backupbackup = link(backup_head);
	if (curcmd < 111)
	{
		if (int_par(tracing_commands_code) > 1)
			showcurcmdchr();
		halfword t;
		smallnumber savescannerstatus;
		halfword p, q, r;
		int j;
		switch (curcmd)
		{
			case 110:
				if (curmark[curchr])
					begintokenlist(curmark[curchr], 14);
				break;
			case 102:
				gettoken();
				t = curtok;
				gettoken();
				if (curcmd > 100)
					expand();
				else
					backinput();
				curtok = t;
				backinput();
				break;
			case 103:
				savescannerstatus = scannerstatus;
				scannerstatus = 0;
				gettoken();
				scannerstatus = savescannerstatus;
				t = curtok;
				backinput();
				if (t >= 4095)
				{
					p = getavail();
					info(p) = 6718;
					link(p) = curinput.locfield;
					curinput.startfield = p;
					curinput.locfield = p;
				}
				break;
			case 107:
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
					if (interaction = 3)
						printnl(262); //! 
					print(625); //Missing 
					printesc(505); //endcsname
					print(626); // inserted
					helpptr = 2;
					helpline[1] = 627; //The control sequence marked <to be read again> should
					helpline[0] = 628; //not appear between \csname and \endcsname.
					backerror();
				}
				j = First;
				p = link(r);
				while (p)
				{
					if (j >= maxbufstack)
					{
						maxbufstack = j+1;
						if (maxbufstack = bufsize)
							overflow(256, bufsize); //buffer size
					};
					buffer[j++] = info(p)%256;
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
				if (eq_type(curcs) == 101)
					eqdefine(curcs, 0, 256);
				curtok = curcs+4095;
				backinput();
				break;
			case 108: 
				convtoks();
				break;
			case 109: 
				insthetoks();
				break;
			case 105: 
				conditional();
				break;
			case 106:
				if (curchr > iflimit)
					if (iflimit = 1)
						insertrelax();
					else
					{
						if (interaction == 3)
							printnl(262); //! 
						print(776); //Extra 
						printcmdchr(106, curchr); 
						{
							helpptr = 1;
							helpline[0] = 777; //I'm ignoring this; it doesn't match any \if.
						}
						error();
					}
				else
				{
					while (curchr != 2)
						passtext();
					p = condptr;
					ifline = mem[p+1].int_;
					curif = subtype(p);
					iflimit = type(p);
					condptr = link(p);
					freenode(p, 2);
				}
				break;
			case 104:
				if (curchr > 0)
					forceeof = true;
				else 
					if (nameinprogress)
						insertrelax();
					else
						startinput();
				break;
			default:
				if (interaction == 3)
					printnl(262); //! 
				print(619); //Undefined control sequence
				helpptr = 5;
				helpline[4] = 620; //The control sequence at the end of the top line
				helpline[3] = 621; //of your error message was never \def'ed. If you have
				helpline[2] = 622; //misspelled it (e.g., `\hobx'), type `I' and the correct
				helpline[1] = 623; //spelling (e.g., `I\hbox'). Otherwise just continue,
				helpline[0] = 624; //and I'll forget about whatever was undefined.
				error();
		}
	}
	else 
		if (curcmd < 115)
			macrocall();
		else
		{
			curtok = 6715;
			backinput();
		}
	curval = cvbackup;
	curvallevel = cvlbackup;
	radix = radixbackup;
	curorder = cobackup;
	link(backup_head) = backupbackup;
}
