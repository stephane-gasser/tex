#include "conditional.h"
#include "getnode.h"
#include "getxtoken.h"
#include "scanint.h"
#include "scandimen.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "backerror.h"
#include "scaneightbitint.h"
#include "getnext.h"
#include "scanfourbitint.h"
#include "begindiagnostic.h"
#include "printint.h"
#include "printchar.h"
#include "enddiagnostic.h"
#include "freenode.h"
#include "passtext.h"
#include "changeiflimit.h"
#include "printesc.h"
#include "error.h"

void conditional(void)
{

	auto p = getnode(2);
	link(p) = condptr;
	type(p) = iflimit;
	subtype(p) = curif;
	mem[p+1].int_ = ifline;
	condptr = p;
	curif = curchr;
	iflimit = 1;
	ifline = line;
	auto savecondptr = condptr;
	smallnumber thisif = curchr;
	halfword q;
	int r;
	bool b;
	int m, n;
	smallnumber savescannerstatus;
	switch (thisif)
	{
		case 0:
		case 1:
			getxtoken();
			if (curcmd == 0)
				if (curchr == 257)
				{
					curcmd = 13;
					curchr = curtok-4096;
				}
			if (curcmd > 13 || curchr > 255)
			{
				m = 0;
				n = 256;
			}
			else
			{
				m = curcmd;
				n = curchr;
			}
			getxtoken;
			if (curcmd == 0)
				if (curchr == 257)
				{
					curcmd = 13;
					curchr = curtok-4096;
				}
			if (curcmd > 13 || curchr > 255)
			{
				curcmd = 0;
				curchr = 256;
			}
			if (thisif == 0)
				b = n == curchr;
			else
				b = m == curcmd;
			break;
		case 2:
		case 3:
			if (thisif == 2)
				scanint();
			else
				scandimen(false, false,	false);
			n = curval;
			do
				getxtoken();
			while (curcmd == 10);
			if (curtok >= 3132 && curtok <= 3134)
				r = curtok-3072;
			else
			{
				if (interaction == 3)
					printnl(262); //! 
				print(780); //Missing = inserted for 
				printcmdchr(105, thisif);
				helpptr = 1;
				helpline[0] = 781; //I was expecting to see `<', `=', or `>'. Didn't.
				backerror();
				r = '=';
			}
			if (thisif == 2)
				scanint();
			else
				scandimen(false, false, false);
			switch (r)
			{
				case '<': 
					b = n < curval;
					break;
				case '=': 
					b = n == curval;
					break;
				case '>': 
					b = n > curval;
			}
			break;
		case 4:
			scanint();
			b = curval%2;
			break;
		case 5: 
			b = abs(curlist.modefield) == 1;
			break;
		case 6: 
			b = abs(curlist.modefield) == 102;
			break;
		case 7: 
			b = abs(curlist.modefield) == 203;
			break;
		case 8: 
			b = curlist.modefield < 0;
			break;
		case 9:
		case 10:
		case 11:
			scaneightbitint();
			p = box(curval);
			if (thisif == 9)
				b = p == 0;
			else 
				if (p == 0)
					b = false;
				else 
					if (thisif == 10)
						b = type(p) == 0;
					else
						b = type(p) == 1;
			break;
		case 12:
			savescannerstatus = scannerstatus;
			scannerstatus = 0;
			getnext();
			n = curcs;
			p = curcmd;
			q = curchr;
			getnext();
			if (curcmd != p)
				b = false;
			else 
				if (curcmd < 111)
					b = curchr == q;
				else
				{
					p = link(curchr);
					q = link(equiv(n));
					if (p == q)
						b = true;
					else
					{
						while (p && q)
							if (info(p) != info(q))
								p = 0;
							else
							{
								p = link(p);
								q = link(q);
							}
						b = p == 0 && q == 0;
					}
				}
			scannerstatus = savescannerstatus;
			break;
		case 13:
			scanfourbitint();
			b = readopen[curval] == 2;
			break;
		case 14: 
			b = true;
			break;
		case 15: 
			b = false;
			break;
		case 16:
			scanint();
			n = curval;
			if (int_par(tracing_commands_code) > 1)
			{
				begindiagnostic();
				print(782); //{case 
				printint(n);
				printchar('}');
				enddiagnostic(false);
			}
			while (n)
			{
				passtext();
				if (condptr == savecondptr)
					if (curchr == 4)
						n--;
					else
					{
						if (curchr == 2)
						{
							p = condptr;
							ifline = mem[p+1].int_;
							curif = subtype(p);
							iflimit = type(p);
							condptr = link(p);
							freenode(p, 2);
						}
						else
							iflimit = 2;
						return;
					}
				else 
					if (curchr == 2)
					{
						p = condptr;
						ifline = mem[p+1].int_;
						curif = subtype(p);
						iflimit = type(p);
						condptr = link(p);
						freenode(p, 2);
					}
			}
			changeiflimit(4, savecondptr);
			return;
	}
	if (int_par(tracing_commands_code) > 1)
	{
		begindiagnostic();
		if (b)
			print(778); //{true}
		else
			print(779); //{false}
		enddiagnostic(false);
	}
	if (b)
	{
		changeiflimit(3, savecondptr);
		return;
	}
	while (true)
	{
		passtext();
		if (condptr == savecondptr)
		{
			if (curchr != 4)
			{
				if (curchr == 2)
				{
					p = condptr;
					ifline = mem[p+1].int_;
					curif = subtype(p);
					iflimit = type(p);
					condptr = link(p);
					freenode(p, 2);
				}
				else
					iflimit = 2;
				return;
			}
			if (interaction == 3)
				printnl(262); //! 
			print(776); //Extra 
			printesc(774); //or
			helpptr = 1;
			helpline[0] = 777; //I'm ignoring this; it doesn't match any \if.
			error();
		}
		else 
			if (curchr == 2)
			{
				p = condptr;
				ifline = mem[p+1].int_;
				curif = subtype(p);
				iflimit = type(p);
				condptr = link(p);
				freenode(p, 2);
			}
	}
}
