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

void prefixedcommand(eightbits cmd, halfword chr)
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
			std::tie(cmd, chr, tok, cs) = getxtoken();
		while (cmd == spacer || cmd == escape);
		if (cmd <= max_non_prefixed_command)
		{
			backerror(tok, "You can't use a prefix with `"+cmdchr(cmd, chr)+"\'", "I'll pretend you didn't say \\long or \\outer or \\global.");
			return;
		}
	}
	if (cmd != def && a%4)
		error("You can't use `"+esc("long")+"' or `"+esc("outer")+"' with `"+cmdchr(cmd, chr)+"\'", "I'll pretend you didn't say \\long or \\outer here.");
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
			p = getrtoken();
			q = scantoks(true, e, p);
			define(a, p, call+a%4, defref); // a%4 = 0:call 1:long_call 2:outer_call 3:long_outer_call
			break;
		case let:
			n = chr;
			p = getrtoken();
			halfword tok;
			if (n == 0)
			{
				do
					std::tie(cmd, chr, tok, std::ignore) = gettoken();
				while (cmd == spacer);
				if (tok == other_token+'=') // other_char + '='
				{
					std::tie(cmd, chr, tok, std::ignore) = gettoken();
					if (cmd == spacer)
						std::tie(cmd, chr, tok, std::ignore) = gettoken();
				}
			}
			else
			{
				std::tie(cmd, chr, q, std::ignore) = gettoken();
				std::tie(cmd, chr, tok, std::ignore) = gettoken();
				backinput(tok);
				backinput(q);
			}
			if (cmd >= call)
				info(chr)++;
			define(a, p, cmd, chr);
			break;
		case shorthand_def:
			n = chr;
			p = getrtoken();
			define(a, p, relax, 256);
			scanoptionalequals();
			switch (n)
			{
				case 0:
					define(a, p, char_given, scancharnum());
					break;
				case 1:
					define(a, p, math_given, scanfifteenbitint());
					break;
				case 2: 
					define(a, p, assign_int, count_base+scaneightbitint());
					break;
				case 3: 
					define(a, p, assign_dimen, scaled_base+scaneightbitint());
					break;
				case 4: 
					define(a, p, assign_glue, skip_base+scaneightbitint());
					break;
				case 5: 
					define(a, p, assign_mu_glue, mu_skip_base+scaneightbitint());
					break;
				case 6: 
					define(a, p, assign_toks, toks_base+scaneightbitint());
			}
			break;
		case read_to_cs:
			n = scanint();
			if (!scankeyword("to")) 
				error("Missing `to' inserted", "You should have said `\\read<number> to \\cs'.\nI'm going to look for the \\cs now.");
			p = getrtoken();
			define(a, p, call, readtoks(n, p));
			break;
		case toks_register:
		case assign_toks:
			q = cs;
			p = cmd == toks_register ? toks_base+scaneightbitint() : chr;
			scanoptionalequals();
			do
				std::tie(cmd, chr, tok, cs) = getxtoken();
			while (cmd == spacer || cmd == escape);
			if (cmd != left_brace)
			{
				if (cmd == toks_register)
				{
					cmd = assign_toks;
					chr = toks_base+scaneightbitint();
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
			q = scantoks(false, false, q);
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
			scanoptionalequals();
			word_define(a, p, scanint());
			break;
		case assign_dimen:
			p = chr;
			scanoptionalequals();
			word_define(a, p, scandimen(false, false, false));
			break;
		case assign_glue:
		case assign_mu_glue:
			p = chr;
			n = cmd;
			scanoptionalequals();
			if (n == assign_mu_glue)
				val = scanglue(3);
			else
				val = scanglue(2);
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
			p = chr+scancharnum();
			scanoptionalequals();
			val = scanint();
			if ((val < 0 && p < del_code_base) || val > n)
			{
				error("Invalid code ("+std::to_string(val)+(p < del_code_base ? "), should be in the range 0.." : "//), should be at most ")+std::to_string(n), "I'm going to use 0 instead of that illegal code value.");
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
			p += scanfourbitint();
			scanoptionalequals();
			define(a, p, data, scanfontident());
			break;
		case register_:
		case advance:
		case multiply:
		case divide: 
			doregistercommand(a, cmd, chr);
			break;
		case set_box:
			n = scaneightbitint();
			if (a >= 4)
				n += 1<<8;
			scanoptionalequals();
			if (setboxallowed)
				scanbox(box_flag+n);
			else
				error("Improper "+esc("setbox"), "Sorry, \\setbox is not allowed after \\halign in a display,\nor between \\accent and an accented character.");
			break;
		case set_aux: 
			alteraux(cmd, chr);
			break;
		case set_prev_graf: 
			alterprevgraf();
			break;
		case set_page_dimen: 
			alterpagesofar(chr);
			break;
		case set_page_int: 
			alterinteger(chr);
			break;
		case set_box_dimen: 
			alterboxdimen(chr);
			break;
		case set_shape:
			scanoptionalequals();
			n = scanint();
			if (n <= 0)
				p = 0;
			else
			{
				p = getnode(2*n+1);
				info(p) = n;
				for (j = 1; j <= n; j++)
				{
					mem[p+2*j-1].int_ = scan_normal_dimen();
					mem[p+2*j].int_ = scan_normal_dimen();
				}
			}
			define(a, par_shape_loc, shape_ref, p);
			break;
		case hyph_data:
			if (chr == 1)
				newpatterns(cs);
			else
				newhyphexceptions();
			break;
		case assign_font_dimen:
			k = findfontdimen(true);
			scanoptionalequals();
			fontinfo[k].int_ = scan_normal_dimen();
			break;
		case assign_font_int:
			n = chr;
			f = scanfontident();
			scanoptionalequals();
			if (n == 0)
				hyphenchar[f] = scanint();
			else
				skewchar[f] = scanint();
			break;
		case def_font: 
			newfont(a);
			break;
		case set_interaction: 
			newinteraction(chr);
			break;
		default: 
			confusion("prefix");
	}
	if (aftertoken)
	{
		backinput(aftertoken);
		aftertoken = 0;
	}
}
