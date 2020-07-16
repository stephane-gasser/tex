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

void initalign(eightbits cmd, halfword cs, halfword &loop)
{
	auto savecsptr = cs;
	pushalignment(loop);
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
	halfword tok;
	std::tie(cmd, std::ignore, tok) = scanspec(6, false);
	link(align_head) = 0;
	curalign = align_head;
	loop = 0;
	scannerstatus = 4;
	warningindex = savecsptr;
	alignstate = -1000000;
	while (true)
	{
		link(curalign) = newparamglue(tab_skip_code);
		curalign = link(curalign);
		if (cmd == car_ret)
			break;
		halfword p = hold_head;
		link(p) = 0;
		halfword tok;
		while (true)
		{
			std::tie(cmd, tok) = getpreambletoken();
			if (cmd == mac_param)
				break;
			if ((cmd == tab_mark || cmd == out_param) && alignstate == -1000000)
				if (p == hold_head && loop == 0 && cmd == tab_mark)
					loop = curalign;
				else
				{
					backerror(tok, "Missing # inserted in alignment preamble", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nnone, so I've put one in; maybe that will work.");
					break;
				}
			else 
				if (cmd != spacer || p != hold_head)
				{
					link(p) = getavail();
					p = link(p);
					info(p) = tok;
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
			std::tie(cmd, tok) = getpreambletoken();
			if (cmd <= out_param && cmd >= tab_mark && alignstate == -1000000)
				break;
			if (cmd == mac_param)
			{
				error("Only one # is allowed per tab", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nmore than one, so I'm ignoring all but the first.");
				continue;
			}
			link(p) = getavail();
			p = link(p);
			info(p) = tok;
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
	alignpeek(loop);
}
