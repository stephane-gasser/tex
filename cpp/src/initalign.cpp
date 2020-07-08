#include "initalign.h"
#include "impression.h"
#include "erreur.h"
#include "flushmath.h"
#include "lecture.h"
#include "pushalignment.h"
#include "pushnest.h"
#include "getavail.h"
#include "noeud.h"
#include "alignpeek.h"
#include "texte.h"

void initalign(void)
{
	auto savecsptr = curcs;
	pushalignment();
	alignstate = -1000000;
	if (mode == mmode && (tail != head || incompleat_noad))
	{
		error("Improper "+esc("halign")+" inside $$'s", "Displays can use special alignments (like \\eqalignno)\nonly if nothing but the alignment itself is between $$'s.\nSo I've deleted the formulas that preceded this alignment.");
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
					backerror("Missing # inserted in alignment preamble", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nnone, so I've put one in; maybe that will work.");
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
				error("Only one # is allowed per tab", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nmore than one, so I'm ignoring all but the first.");
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
