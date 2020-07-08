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
#include "getnode.h"
#include "noeud.h"
#include "findfontdimen.h"
#include "texte.h"

void prefixedcommand(void)
{
	smallnumber a;
	internalfontnumber f;
	halfword j;
	fontindex k;
	halfword p, q;
	int n;
	bool e;
	a = 0;
	while (curcmd == prefix)
	{
		if ((a/curchr)%2 == 0)
			a += curchr;
		do
			getxtoken();
		while (curcmd == spacer || curcmd == escape);
		if (curcmd <= max_non_prefixed_command)
		{
			backerror("You can't use a prefix with `"+cmdchr(curcmd, curchr)+"\'", "I'll pretend you didn't say \\long or \\outer or \\global.");
			return;
		}
	}
	if (curcmd != def && a%4)
		error("You can't use `"+esc("long")+"' or `"+esc("outer")+"' with `"+cmdchr(curcmd, curchr)+"\'", "I'll pretend you didn't say \\long or \\outer here.");
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
	switch (curcmd)
	{
		case set_font: 
			define(a, cur_font_loc, data, curchr);
			break;
		case def:
			if (curchr%2 & a < 4 && global_defs() >= 0)
				a += 4;
			e = curchr >= 2;
			getrtoken();
			p = curcs;
			q = scantoks(true, e);
			define(a, p, 111+a%4, defref); // a%4 = 0:call 1:long_call 2:outer_call 3:long_outer_call
			break;
		case let:
			n = curchr;
			getrtoken();
			p = curcs;
			if (n == 0)
			{
				do
					gettoken();
				while (curcmd == spacer);
				if (curtok == 3133) // other_char + '='
				{
					gettoken();
					if (curcmd == spacer)
						gettoken();
				}
			}
			else
			{
				gettoken();
				q = curtok;
				gettoken();
				backinput();
				curtok = q;
				backinput;
			}
			if (curcmd >= call)
				info(curchr)++;
			define(a, p, curcmd, curchr);
			break;
		case shorthand_def:
			n = curchr;
			getrtoken();
			p = curcs;
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
				default:
					switch (n)
					{
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
			}
			break;
		case read_to_cs:
			n = scanint();
			if (!scankeyword("to")) 
				error("Missing `to' inserted", "You should have said `\\read<number> to \\cs'.\nI'm going to look for the \\cs now.");
			getrtoken();
			p = curcs;
			define(a, p, call, readtoks(n, p));
			break;
		case toks_register:
		case assign_toks:
			q = curcs;
			if (curcmd == toks_register)
				p = toks_base+scaneightbitint();
			else
				p = curchr;
			scanoptionalequals();
			do
				getxtoken();
			while (curcmd == spacer || curcmd == escape);
			if (curcmd != left_brace)
			{
				if (curcmd == toks_register)
				{
					curcmd = assign_toks;
					curchr = toks_base+scaneightbitint();
				}
				if (curcmd == assign_toks)
				{
					q = equiv(curchr);
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
			backinput();
			curcs = q;
			q = scantoks(false, false);
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
			p = curchr;
			scanoptionalequals();
			word_define(a, p, scanint());
			break;
		case assign_dimen:
			p = curchr;
			scanoptionalequals();
			word_define(a, p, scandimen(false, false, false));
			break;
		case assign_glue:
		case assign_mu_glue:
			p = curchr;
			n = curcmd;
			scanoptionalequals();
			if (n == assign_mu_glue)
				val = scanglue(3);
			else
				val = scanglue(2);
			trapzeroglue(val);
			define(a, p, glue_ref, val);
			break;
		case def_code:
			if (curchr == cat_code_base)
				n = 0x0F;
			else 
				if (curchr == math_code_base)
					n = 0x80'00;
				else 
					if (curchr == sf_code_base)
						n = 0x7F'FF;
					else 
						if (curchr == del_code_base)
							n = 0xFF'FF'FF;
						else
						n = 0xFF;
			p = curchr;
			p += scancharnum();
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
			p = curchr;
			p += scanfourbitint();
			scanoptionalequals();
			define(a, p, data, scanfontident());
			break;
		case register_:
		case advance:
		case multiply:
		case divide: 
			doregistercommand(a);
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
			alteraux();
			break;
		case set_prev_graf: 
			alterprevgraf();
			break;
		case set_page_dimen: 
			alterpagesofar();
			break;
		case set_page_int: 
			alterinteger();
			break;
		case set_box_dimen: 
			alterboxdimen();
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
			if (curchr == 1)
				newpatterns();
			else
				newhyphexceptions();
			break;
		case assign_font_dimen:
			k = findfontdimen(true);
			scanoptionalequals();
			fontinfo[k].int_ = scan_normal_dimen();
			break;
		case assign_font_int:
			n = curchr;
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
			newinteraction();
			break;
		default: 
			confusion("prefix");
	}
	if (aftertoken)
	{
		curtok = aftertoken;
		backinput();
		aftertoken = 0;
	}
}
