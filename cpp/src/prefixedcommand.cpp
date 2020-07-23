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
#include "cesure.h"
#include "police.h"

void prefixedcommand(Token t, bool setboxallowed)
{
	internalfontnumber f;
	halfword j;
	fontindex k;
	halfword p, q;
	int n;
	bool e;
	smallnumber a = 0;
	while (t.cmd == prefix)
	{
		if ((a/t.chr)%2 == 0)
			a += t.chr;
		t = getXTokenSkipSpaceAndEscape();
		if (t.cmd <= max_non_prefixed_command)
		{
			backerror(t, "You can't use a prefix with `"+cmdchr(t)+"\'", "I'll pretend you didn't say \\long or \\outer or \\global.");
			return;
		}
	}
	if (t.cmd != def && a%4)
		error("You can't use `"+esc("long")+"' or `"+esc("outer")+"' with `"+cmdchr(t)+"\'", "I'll pretend you didn't say \\long or \\outer here.");
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
	switch (t.cmd)
	{
		case set_font:
			define(a, cur_font_loc, data, t.chr);
			break;
		case def:
			if (t.chr%2 & a < 4 && global_defs() >= 0)
				a += 4;
			e = t.chr >= 2;
			p = getrtoken();
			Token tk;
			tk.cs = p;
			q = scantoks(true, e, tk);
			define(a, p, call+a%4, defref); // a%4 = 0:call 1:long_call 2:outer_call 3:long_outer_call
			break;
		case let:
			n = t.chr;
			p = getrtoken();
			if (n == 0)
			{
				t = getXTokenSkipSpace();
				if (t.tok == other_token+'=') // other_char + '='
				{
					t = gettoken();
					if (t.cmd == spacer)
						t = gettoken();
				}
			}
			else
			{
				auto tt = gettoken();
				t = gettoken();
				backinput(t);
				backinput(tt);
			}
			if (t.cmd >= call)
				info(t.chr)++;
			define(a, p, t.cmd, t.chr);
			break;
		case shorthand_def:
			n = t.chr;
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
			q = t.cs;
			p = t.cmd == toks_register ? toks_base+scaneightbitint() : t.chr;
			scanoptionalequals();
			t = getXTokenSkipSpaceAndEscape();
			if (t.cmd != left_brace)
			{
				if (t.cmd == toks_register)
				{
					t.cmd = assign_toks;
					t.chr = toks_base+scaneightbitint();
				}
				if (t.cmd == assign_toks)
				{
					q = equiv(t.chr);
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
			backinput(t);
			tk.cs = q;
			q = scantoks(false, false, tk);
			if (link(defref) == 0)
			{
				define(a, p, undefined_cs, 0);
				link(defref) = avail;
				avail = defref;
			}
			else
			{
				if (p == output_routine_loc) 
				{
					link(q) = getavail();
					q = link(q);
					info(q) = right_brace_token+'}';
					q = getavail();
					info(q) = left_brace_token+'{';
					link(q) = link(defref);
					link(defref) = q;
				}
				define(a, p, call, defref);
			}
			break;
		case assign_int:
			p = t.chr;
			scanoptionalequals();
			word_define(a, p, scanint());
			break;
		case assign_dimen:
			p = t.chr;
			scanoptionalequals();
			word_define(a, p, scandimen(false, false, false));
			break;
		case assign_glue:
		case assign_mu_glue:
			p = t.chr;
			n = t.cmd;
			scanoptionalequals();
			if (n == assign_mu_glue)
				val = scanglue(3);
			else
				val = scanglue(2);
			trapzeroglue(val);
			define(a, p, glue_ref, val);
			break;
		case def_code:
			switch (t.chr)
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
			p = t.chr+scancharnum();
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
			p = t.chr;
			p += scanfourbitint();
			scanoptionalequals();
			define(a, p, data, scanfontident());
			break;
		case register_:
		case advance:
		case multiply:
		case divide: 
			doregistercommand(a, t);
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
			alteraux(t);
			break;
		case set_prev_graf: 
			alterprevgraf();
			break;
		case set_page_dimen: 
			alterpagesofar(t);
			break;
		case set_page_int: 
			alterinteger(t);
			break;
		case set_box_dimen: 
			alterboxdimen(t);
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
			if (t.chr == 1)
				newpatterns(t);
			else
				newhyphexceptions();
			break;
		case assign_font_dimen:
			k = findfontdimen(true);
			scanoptionalequals();
			fontinfo[k].int_ = scan_normal_dimen();
			break;
		case assign_font_int:
			n = t.chr;
			f = scanfontident();
			scanoptionalequals();
			if (n == 0)
				fonts[f].hyphenchar = scanint();
			else
				fonts[f].skewchar = scanint();
			break;
		case def_font: 
			newfont(a);
			break;
		case set_interaction: 
			newinteraction(t);
			break;
		default: 
			confusion("prefix");
	}
	if (aftertoken.tok)
	{
		backinput(aftertoken);
		aftertoken.tok = 0;
	}
}
