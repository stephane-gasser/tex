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

[[nodiscard]] static Token get_x_token_or_active_char(void)
{ 
	auto t = getxtoken(); 
	if (t.cmd == relax)
		if (t.chr == no_expand_flag)
		{
			t.cmd = active_char; 
			t.chr = t.tok-cs_token_flag-active_base; 
		}
	return t;
}

void conditional(Token t)
{
	auto p = getnode(2);
	link(p) = condptr;
	type(p) = iflimit;
	subtype(p) = curif;
	if_line_field(p) = ifline;
	condptr = p;
	curif = t.chr;
	iflimit = 1;
	ifline = line;
	auto savecondptr = condptr;
	smallnumber thisif = t.chr;
	halfword q;
	int r;
	bool b;
	int m, n;
	smallnumber savescannerstatus;
	switch (thisif)
	{
		case if_char_code:
		case if_cat_code:
			t = get_x_token_or_active_char();
			if (t.cmd > active_char || t.chr > 255)
			{
				m = relax;
				n = 256;
			}
			else
			{
				m = t.cmd;
				n = t.chr;
			}
			t = get_x_token_or_active_char();
			if (t.cmd > active_char || t.chr > 255)
			{
				t.cmd = relax;
				t.chr = 256;
			}
			if (thisif == if_char_code)
				b = n == t.chr;
			else
				b = m == t.cmd;
			break;
		case if_int_code:
		case if_dim_code:
			n = thisif == if_int_code ? scanint() : scan_normal_dimen();
			t = getXTokenSkipSpace();
			if (t.tok >= other_token+'<' && t.tok <= other_token+'>')
				r = t.tok-other_token;
			else
			{
				Token tk;
				tk.cmd = if_test;
				tk.chr = thisif;
				backerror(t, "Missing = inserted for "+cmdchr(tk), "I was expecting to see `<', `=', or `>'. Didn't.");
				r = '=';
			}
			switch (r)
			{
				case '<': 
					b = thisif == if_int_code ? n < scanint() : n < scan_normal_dimen();
					break;
				case '=': 
					b = thisif == if_int_code ? n == scanint() : n == scan_normal_dimen();
					break;
				case '>': 
					b = thisif == if_int_code ? n > scanint() : n > scan_normal_dimen();
			}
			break;
		case if_odd_code:
			b = scanint()%2;
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
			p = box[scaneightbitint()]->num;
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
			t = getnext();
			p = t.cmd;
			q = t.chr;
			r = t.cs;
			t = getnext();
			if (t.cmd != p)
				b = false;
			else 
				if (t.cmd < call)
					b = t.chr == q;
				else
				{
					p = link(t.chr);
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
			b = readopen[scanfourbitint()] == 2;
			break;
		case if_true_code: 
			b = true;
			break;
		case if_false_code: 
			b = false;
			break;
		case if_case_code:
			n = scanint();
			if (tracing_commands() > 1)
				diagnostic("{case "+std::to_string(n)+"}");
			while (n)
			{
				passtext();
				if (condptr == savecondptr)
					if (t.chr == 4)
						n--;
					else
					{
						if (t.chr == 2)
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
					if (t.chr == 2)
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
			if (t.chr != 4)
			{
				if (t.chr == 2)
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
			if (t.chr == 2)
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
