#include "conditional.h"
#include "noeud.h"
#include "lecture.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"
#include "passtext.h"
#include "changeiflimit.h"
#include "erreur.h"
#include "texte.h"

[[nodiscard]] static std::tuple<eightbits, halfword> get_x_token_or_active_char(halfword align)
{ 
	auto [cmd, chr, tok, cs] = getxtoken(align); 
	if (cmd == relax)
		if (chr == no_expand_flag)
		{
			cmd = active_char; 
			chr = tok-cs_token_flag-active_base; 
		}
	return std::make_tuple(cmd, chr);
}

void conditional(halfword chr, halfword align)
{
	auto p = getnode(2);
	link(p) = condptr;
	type(p) = iflimit;
	subtype(p) = curif;
	if_line_field(p) = ifline;
	condptr = p;
	curif = chr;
	iflimit = 1;
	ifline = line;
	auto savecondptr = condptr;
	smallnumber thisif = chr;
	halfword q;
	int r;
	bool b;
	int m, n;
	smallnumber savescannerstatus;
	halfword cs;
	eightbits cmd;
	switch (thisif)
	{
		case if_char_code:
		case if_cat_code:
			std::tie(cmd, chr) = get_x_token_or_active_char(align);
			if (cmd > active_char || chr > 255)
			{
				m = relax;
				n = 256;
			}
			else
			{
				m = cmd;
				n = chr;
			}
			std::tie(cmd, chr) = get_x_token_or_active_char(align);
			if (cmd > 13 || chr > 255)
			{
				cmd = relax;
				chr = 256;
			}
			if (thisif == if_char_code)
				b = n == chr;
			else
				b = m == cmd;
			break;
		case if_int_code:
		case if_dim_code:
			if (thisif == if_int_code)
				n = scanint(align);
			else
				n = scan_normal_dimen(align);
			halfword tok;
			do
				std::tie(cmd, std::ignore, tok, std::ignore) = getxtoken(align);
			while (cmd == spacer);
			if (tok >= other_token+'<' && tok <= other_token+'>')
				r = tok-other_token;
			else
			{
				backerror(tok, "Missing = inserted for "+cmdchr(if_test, thisif), "I was expecting to see `<', `=', or `>'. Didn't.", align);
				r = '=';
			}
			switch (r)
			{
				case '<': 
					b = thisif == if_int_code ? n < scanint(align) : n < scan_normal_dimen(align);
					break;
				case '=': 
					b = thisif == if_int_code ? n == scanint(align) : n == scan_normal_dimen(align);
					break;
				case '>': 
					b = thisif == if_int_code ? n > scanint(align) : n > scan_normal_dimen(align);
			}
			break;
		case if_odd_code:
			b = scanint(align)%2;
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
			p = box(scaneightbitint(align));
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
			std::tie(p, q, r) = getnext(align);
			std::tie(cmd, chr, cs) = getnext(align);
			if (cmd != p)
				b = false;
			else 
				if (cmd < call)
					b = chr == q;
				else
				{
					p = link(chr);
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
			b = readopen[scanfourbitint(align)] == 2;
			break;
		case if_true_code: 
			b = true;
			break;
		case if_false_code: 
			b = false;
			break;
		case if_case_code:
			n = scanint(align);
			if (tracing_commands() > 1)
				diagnostic("{case "+std::to_string(n)+"}");
			while (n)
			{
				passtext(align);
				if (condptr == savecondptr)
					if (chr == 4)
						n--;
					else
					{
						if (chr == 2)
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
					if (chr == 2)
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
		passtext(align);
		if (condptr == savecondptr)
		{
			if (chr != 4)
			{
				if (chr == 2)
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
			error("Extra "+esc("or"), "I'm ignoring this; it doesn't match any \\if.", align);
		}
		else 
			if (chr == 2)
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
