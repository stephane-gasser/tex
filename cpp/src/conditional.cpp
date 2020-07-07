#include "conditional.h"
#include "getnode.h"
#include "lecture.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"
#include "freenode.h"
#include "passtext.h"
#include "changeiflimit.h"
#include "erreur.h"
#include "texte.h"

static void get_x_token_or_active_char(void)
{ 
	getxtoken(); 
	if (curcmd == relax)
		if (curchr == no_expand_flag)
		{
			curcmd = active_char; 
			curchr = curtok-cs_token_flag-active_base; 
		}
}

void conditional(void)
{
	auto p = getnode(2);
	link(p) = condptr;
	type(p) = iflimit;
	subtype(p) = curif;
	if_line_field(p) = ifline;
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
		case if_char_code:
		case if_cat_code:
			get_x_token_or_active_char();
			if (curcmd > active_char || curchr > 255)
			{
				m = relax;
				n = 256;
			}
			else
			{
				m = curcmd;
				n = curchr;
			}
			get_x_token_or_active_char();
			if (curcmd > 13 || curchr > 255)
			{
				curcmd = relax;
				curchr = 256;
			}
			if (thisif == if_char_code)
				b = n == curchr;
			else
				b = m == curcmd;
			break;
		case if_int_code:
		case if_dim_code:
			if (thisif == if_int_code)
				curval = scanint();
			else
				curval = scan_normal_dimen();
			n = curval;
			do
				getxtoken();
			while (curcmd == spacer);
			if (curtok >= 0x0C'00+'<' && curtok <= 0x0C'00+'>')
				r = curtok-0x0C'00;
			else
			{
				backerror("Missing = inserted for "+cmdchr(if_test, thisif), "I was expecting to see `<', `=', or `>'. Didn't.");
				r = '=';
			}
			if (thisif == if_int_code)
				curval = scanint();
			else
				curval = scan_normal_dimen();
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
		case if_odd_code:
			curval = scanint();
			b = curval%2;
			break;
		case if_vmode_code: 
			b = abs(mode) == vmode;
			break;
		case if_hmode_code: 
			b = abs(mode) == hmode;
			break;
		case if_mmode_code: 
			b = abs(mode) == mmode;
			break;
		case if_inner_code: 
			b = mode < 0;
			break;
		case if_void_code:
		case if_hbox_code:
		case if_vbox_code:
			curval = scaneightbitint();
			p = box(curval);
			if (thisif == if_void_code)
				b = p == 0;
			else 
				if (p == 0)
					b = false;
				else 
					if (thisif == if_hbox_code)
						b = type(p) == 0;
					else
						b = type(p) == 1;
			break;
		case ifx_code:
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
				if (curcmd < call)
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
		case if_eof_code:
			curval = scanfourbitint();
			b = readopen[curval] == 2;
			break;
		case if_true_code: 
			b = true;
			break;
		case if_false_code: 
			b = false;
			break;
		case if_case_code:
			curval = scanint();
			n = curval;
			if (tracing_commands() > 1)
				diagnostic("{case "+std::to_string(n)+"}");
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
							ifline = if_line_field(p);
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
						ifline = if_line_field(p);
						curif = subtype(p);
						iflimit = type(p);
						condptr = link(p);
						freenode(p, 2);
					}
			}
			changeiflimit(4, savecondptr);
			return;
	}
	if (tracing_commands() > 1)
		diagnostic(b ? "{true}" : "{false}");
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
					ifline = if_line_field(p);
					curif = subtype(p);
					iflimit = type(p);
					condptr = link(p);
					freenode(p, 2);
				}
				else
					iflimit = 2;
				return;
			}
			error("Extra "+esc("or"), "I'm ignoring this; it doesn't match any \\if.");
		}
		else 
			if (curchr == 2)
			{
				p = condptr;
				ifline = if_line_field(p);
				curif = subtype(p);
				iflimit = type(p);
				condptr = link(p);
				freenode(p, 2);
			}
	}
}
