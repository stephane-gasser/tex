#include "initalign.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"
#include "flushmath.h"
#include "scanspec.h"
#include "pushalignment.h"
#include "pushnest.h"
#include "newparamglue.h"
#include "getpreambletoken.h"
#include "backerror.h"
#include "getavail.h"
#include "newnullbox.h"
#include "newsavelevel.h"
#include "begintokenlist.h"
#include "alignpeek.h"

void initalign(void)
{
	auto savecsptr = curcs;
	pushalignment();
	alignstate = -1000000;
	if (curlist.modefield == 203 && (curlist.tailfield != curlist.headfield || curlist.auxfield.int_))
	{
		if (interaction == 3)
			printnl(262); //! 
		print(680); //Improper 
		printesc(520); //halign
		print(893); // inside $$'s
		helpptr = 3;
		helpline[2] = 894; //Displays can use special alignments (like \eqalignno)
		helpline[1] = 895; //only if nothing but the alignment itself is between $$'s.
		helpline[0] = 896; //So I've deleted the formulas that preceded this alignment.
		error();
		flushmath();
	}
	pushnest();
	if (curlist.modefield == 203)
	{
		curlist.modefield = -1;
		curlist.auxfield.int_ = nest[nestptr-2].auxfield.int_;
	}
	else 
		if (curlist.modefield > 0)
		curlist.modefield = -curlist.modefield;
	scanspec(6, false);
	link(align_head) = 0;
	curalign = align_head;
	curloop = 0;
	scannerstatus = 4;
	warningindex = savecsptr;
	alignstate = -1000000;
	halfword p;
	while (true)
	{
		link(curalign) = newparamglue(11);
		curalign = link(curalign);
		if (curcmd == 5)
			break;
		p = hold_head;
		link(p) = 0;
		while (true)
		{
			getpreambletoken();
			if (curcmd == 6)
				break;
			if (curcmd <= 5 && curcmd >= 4 &&alignstate == -1000000)
				if (p == hold_head && curloop == 0 &&curcmd == 4)
					curloop = curalign;
				else
				{
					if (interaction == 3)
						printnl(262); //! 
					print(902); //Missing # inserted in alignment preamble
					helpptr = 3;
					helpline[2] = 903; //There should be exactly one # between &'s, when an
					helpline[1] = 904; //\halign or \valign is being set up. In this case you had
					helpline[0] = 905; //none, so I've put one in; maybe that will work.
					backerror();
					break;
				}
			else 
				if (curcmd != 10 || p != hold_head)
				{
					link(p) = getavail();
					p = link(p);
					info(p) = curtok;
				}
		}
		link(curalign) = newnullbox();
		curalign = link(curalign);
		info(curalign) = end_span;
		mem[curalign+1].int_ = -1073741824;
		mem[curalign+3].int_ = link(hold_head);
		p = hold_head;
		link(p) = 0;
		while (true)
		{
			getpreambletoken();
			if (curcmd <= 5 && curcmd >= 4 &&alignstate == -1000000)
				break;
			if (curcmd == 6)
			{
				if (interaction == 3)
					printnl(262); //!
				print(906); //Only one # is allowed per tab
				helpptr = 3;
				helpline[2] = 903; //There should be exactly one # between &'s, when an
				helpline[1] = 904; //\halign or \valign is being set up. In this case you had
				helpline[0] = 907; //more than one, so I'm ignoring all but the first.
				error();
				continue;
			}
			link(p) = getavail();
			p = link(p);
			info(p) = curtok;
		}
		link(p) = getavail();
		p = link(p);
		info(p) = 6714;
		mem[curalign+2].int_ = link(hold_head);
	}
	scannerstatus = 0;
	newsavelevel(6);
	if (every_cr())
		begintokenlist(every_cr(), 13);
	alignpeek();
}
