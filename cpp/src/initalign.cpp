#include "initalign.h"
#include "impression.h"
#include "erreur.h"
#include "flushmath.h"
#include "scanspec.h"
#include "pushalignment.h"
#include "pushnest.h"
#include "newparamglue.h"
#include "getpreambletoken.h"
#include "getavail.h"
#include "newnullbox.h"
#include "newsavelevel.h"
#include "begintokenlist.h"
#include "alignpeek.h"
#include "texte.h"

static void erreurInitalign1(void)
{
	print_err("Improper "+esc("halign")+" inside $$'s");
	helpptr = 3;
	helpline[2] = "Displays can use special alignments (like \\eqalignno)";
	helpline[1] = "only if nothing but the alignment itself is between $$'s.";
	helpline[0] = "So I've deleted the formulas that preceded this alignment.";
	error();
}

static void erreurInitalign2(void)
{
	print_err("Missing # inserted in alignment preamble");
	helpptr = 3;
	helpline[2] = "There should be exactly one # between &'s, when an";
	helpline[1] = "\\halign or \\valign is being set up. In this case you had";
	helpline[0] = "none, so I've put one in; maybe that will work.";
}

static void erreurInitalign3(void)
{
	print_err("Only one # is allowed per tab");
	helpptr = 3;
	helpline[2] = "There should be exactly one # between &'s, when an";
	helpline[1] = "\\halign or \\valign is being set up. In this case you had";
	helpline[0] = "more than one, so I'm ignoring all but the first.";
	error();
}

void initalign(void)
{
	auto savecsptr = curcs;
	pushalignment();
	alignstate = -1000000;
	if (mode == mmode && (tail != head || incompleat_noad))
	{
		erreurInitalign1();
		flushmath();
	}
	pushnest();
	if (mode == mmode)
	{
		mode = -1;
		incompleat_noad = nest[nestptr-2].auxfield.int_;
	}
	else 
		if (mode > 0)
		mode = -mode;
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
		if (curcmd == car_ret)
			break;
		p = hold_head;
		link(p) = 0;
		while (true)
		{
			getpreambletoken();
			if (curcmd == mac_param)
				break;
			if (curcmd <= out_param && curcmd >= tab_mark &&alignstate == -1000000)
				if (p == hold_head && curloop == 0 && curcmd == tab_mark)
					curloop = curalign;
				else
				{
					erreurInitalign2();
					backerror();
					break;
				}
			else 
				if (curcmd != spacer || p != hold_head)
				{
					link(p) = getavail();
					p = link(p);
					info(p) = curtok;
				}
		}
		link(curalign) = newnullbox();
		curalign = link(curalign);
		info(curalign) = end_span;
		width(curalign) = null_flag;
		u_part(curalign) = link(hold_head);
		p = hold_head;
		link(p) = 0;
		while (true)
		{
			getpreambletoken();
			if (curcmd <= out_param && curcmd >= tab_mark && alignstate == -1000000)
				break;
			if (curcmd == mac_param)
			{
				erreurInitalign3();
				continue;
			}
			link(p) = getavail();
			p = link(p);
			info(p) = curtok;
		}
		link(p) = getavail();
		p = link(p);
		info(p) = end_template_token;
		v_part(curalign) = link(hold_head);
	}
	scannerstatus = normal;
	newsavelevel(align_group);
	if (every_cr())
		begintokenlist(every_cr(), every_cr_text);
	alignpeek();
}
