#include "prefixedcommand.h"
#include "impression.h"
#include "erreur.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "backinput.h"
#include "getavail.h"
#include "eqworddefine.h"
#include "trapzeroglue.h"
#include "geqworddefine.h"
#include "doregistercommand.h"
#include "lecture.h"
#include "alteraux.h"
#include "alterprevgraf.h"
#include "alterpagesofar.h"
#include "alterboxdimen.h"
#include "alterinteger.h"
#include "noeud.h"
#include "findfontdimen.h"
#include "texte.h"

void prefixedcommand(eightbits cmd, halfword chr, halfword align)
{
	internalfontnumber f;
	halfword j;
	fontindex k;
	halfword p, q;
	int n;
	bool e;
	smallnumber a = 0;
	halfword cs, tok;
	while (cmd == prefix)
	{
		if ((a/chr)%2 == 0)
			a += chr;
		do
			std::tie(cmd, chr, tok, cs) = getxtoken(align);
		while (cmd == spacer || cmd == escape);
		if (cmd <= max_non_prefixed_command)
		{
			backerror(tok, "You can't use a prefix with `"+cmdchr(cmd, chr)+"\'", "I'll pretend you didn't say \\long or \\outer or \\global.", align);
			return;
		}
	}
	if (cmd != def && a%4)
		error("You can't use `"+esc("long")+"' or `"+esc("outer")+"' with `"+cmdchr(cmd, chr)+"\'", "I'll pretend you didn't say \\long or \\outer here.", align);
	if (global_defs())
		if (global_defs() < 0)
		{
			if (a >= 4)
				a -= 4;
		}
		else 
			if (a < 4)
			a += 4;
	int val;
	switch (cmd)
	{
		case set_font: 
			define(a, cur_font_loc, data, chr);
			break;
		case def:
			if (chr%2 & a < 4 && global_defs() >= 0)
				a += 4;
			e = chr >= 2;
			p = getrtoken(align);
			q = scantoks(true, e, p, align);
			define(a, p, call+a%4, defref); // a%4 = 0:call 1:long_call 2:outer_call 3:long_outer_call
			break;
		case let:
			n = chr;
			p = getrtoken(align);
			halfword tok;
			if (n == 0)
			{
				do
					std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
				while (cmd == spacer);
				if (tok == other_token+'=') // other_char + '='
				{
					std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
					if (cmd == spacer)
						std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
				}
			}
			else
			{
				std::tie(cmd, chr, q, std::ignore) = gettoken(align);
				std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
				backinput(tok);
				backinput(q);
			}
			if (cmd >= call)
				info(chr)++;
			define(a, p, cmd, chr);
			break;
		case shorthand_def:
			n = chr;
			p = getrtoken(align);
			define(a, p, relax, 256);
			scanoptionalequals(align);
			switch (n)
			{
				case 0:
					define(a, p, char_given, scancharnum(align));
					break;
				case 1:
					define(a, p, math_given, scanfifteenbitint(align));
					break;
				case 2: 
					define(a, p, assign_int, count_base+scaneightbitint(align));
					break;
				case 3: 
					define(a, p, assign_dimen, scaled_base+scaneightbitint(align));
					break;
				case 4: 
					define(a, p, assign_glue, skip_base+scaneightbitint(align));
					break;
				case 5: 
					define(a, p, assign_mu_glue, mu_skip_base+scaneightbitint(align));
					break;
				case 6: 
					define(a, p, assign_toks, toks_base+scaneightbitint(align));
			}
			break;
		case read_to_cs:
			n = scanint(align);
			if (!scankeyword("to", align)) 
				error("Missing `to' inserted", "You should have said `\\read<number> to \\cs'.\nI'm going to look for the \\cs now.", align);
			p = getrtoken(align);
			define(a, p, call, readtoks(n, p, align));
			break;
		case toks_register:
		case assign_toks:
			q = cs;
			p = cmd == toks_register ? toks_base+scaneightbitint(align) : chr;
			scanoptionalequals(align);
			do
				std::tie(cmd, chr, tok, cs) = getxtoken(align);
			while (cmd == spacer || cmd == escape);
			if (cmd != left_brace)
			{
				if (cmd == toks_register)
				{
					cmd = assign_toks;
					chr = toks_base+scaneightbitint(align);
				}
				if (cmd == assign_toks)
				{
					q = equiv(chr);
					if (q == 0)
						define(a, p, undefined_cs, 0);
					else
					{
						info(q)++;
						define(a, p, call, q);
					}
					break;
				}
			}
			backinput(tok);
			q = scantoks(false, false, q, align);
			if (link(defref) == 0)
			{
				define(a, p, undefined_cs, 0);
				link(defref) = avail;
				avail = defref;
			}
			else
			{
				if (p == 3413) //match +'U'/85 ?
				{
					link(q) = getavail();
					q = link(q);
					info(q) = right_brace*0x01'00+'}';
					q = getavail();
					info(q) = left_brace*0x01'00+'{';
					link(q) = link(defref);
					link(defref) = q;
				}
				define(a, p, call, defref);
			}
			break;
		case assign_int:
			p = chr;
			scanoptionalequals(align);
			word_define(a, p, scanint(align));
			break;
		case assign_dimen:
			p = chr;
			scanoptionalequals(align);
			word_define(a, p, scandimen(false, false, false, align));
			break;
		case assign_glue:
		case assign_mu_glue:
			p = chr;
			n = cmd;
			scanoptionalequals(align);
			if (n == assign_mu_glue)
				val = scanglue(3, align);
			else
				val = scanglue(2, align);
			trapzeroglue(val);
			define(a, p, glue_ref, val);
			break;
		case def_code:
			switch (chr)
			{
				case cat_code_base:
					n = 0x0F;
					break;
				case math_code_base:
					n = 0x80'00;
					break;
				case sf_code_base:
					n = 0x7F'FF;
					break;
				case del_code_base:
					n = 0xFF'FF'FF;
					break;
				default:
					n = 0xFF;
			}
			p = chr+scancharnum(align);
			scanoptionalequals(align);
			val = scanint(align);
			if ((val < 0 && p < del_code_base) || val > n)
			{
				error("Invalid code ("+std::to_string(val)+(p < del_code_base ? "), should be in the range 0.." : "//), should be at most ")+std::to_string(n), "I'm going to use 0 instead of that illegal code value.", align);
				val = 0;
			}
			if (p < math_code_base)
				define(a, p, data, val);
			else 
				if (p < del_code_base)
					define(a, p, data, val);
				else 
					word_define(a, p, val);
			break;
		case def_family:
			p = chr;
			p += scanfourbitint(align);
			scanoptionalequals(align);
			define(a, p, data, scanfontident(align));
			break;
		case register_:
		case advance:
		case multiply:
		case divide: 
			doregistercommand(a, cmd, chr, align);
			break;
		case set_box:
			n = scaneightbitint(align);
			if (a >= 4)
				n += 1<<8;
			scanoptionalequals(align);
			if (setboxallowed)
				scanbox(box_flag+n, align);
			else
				error("Improper "+esc("setbox"), "Sorry, \\setbox is not allowed after \\halign in a display,\nor between \\accent and an accented character.", align);
			break;
		case set_aux: 
			alteraux(cmd, chr, align);
			break;
		case set_prev_graf: 
			alterprevgraf(align);
			break;
		case set_page_dimen: 
			alterpagesofar(chr, align);
			break;
		case set_page_int: 
			alterinteger(chr, align);
			break;
		case set_box_dimen: 
			alterboxdimen(chr, align);
			break;
		case set_shape:
			scanoptionalequals(align);
			n = scanint(align);
			if (n <= 0)
				p = 0;
			else
			{
				p = getnode(2*n+1);
				info(p) = n;
				for (j = 1; j <= n; j++)
				{
					mem[p+2*j-1].int_ = scan_normal_dimen(align);
					mem[p+2*j].int_ = scan_normal_dimen(align);
				}
			}
			define(a, par_shape_loc, shape_ref, p);
			break;
		case hyph_data:
			if (chr == 1)
				newpatterns(cs, align);
			else
				newhyphexceptions(align);
			break;
		case assign_font_dimen:
			k = findfontdimen(true, align);
			scanoptionalequals(align);
			fontinfo[k].int_ = scan_normal_dimen(align);
			break;
		case assign_font_int:
			n = chr;
			f = scanfontident(align);
			scanoptionalequals(align);
			if (n == 0)
				hyphenchar[f] = scanint(align);
			else
				skewchar[f] = scanint(align);
			break;
		case def_font: 
			newfont(a, align);
			break;
		case set_interaction: 
			newinteraction(chr);
			break;
		default: 
			confusion("prefix", align);
	}
	if (aftertoken)
	{
		backinput(aftertoken);
		aftertoken = 0;
	}
}
