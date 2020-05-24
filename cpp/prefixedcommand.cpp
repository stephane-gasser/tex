#include "prefixedcommand.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "printchar.h"
#include "backerror.h"
#include "printesc.h"
#include "error.h"
#include "getrtoken.h"
#include "geqdefine.h"
#include "scantoks.h"
#include "gettoken.h"
#include "eqdefine.h"
#include "scanoptionalequals.h"
#include "backinput.h"
#include "scancharnum.h"
#include "scanfifteenbitint.h"
#include "scaneightbitint.h"
#include "scanint.h"
#include "readtoks.h"
#include "scankeyword.h"
#include "getavail.h"
#include "eqworddefine.h"
#include "scandimen.h"
#include "scanglue.h"
#include "trapzeroglue.h"
#include "geqworddefine.h"
#include "scancharnum.h"
#include "scanfourbitint.h"
#include "scanfontident.h"
#include "printint.h"
#include "doregistercommand.h"
#include "scanbox.h"
#include "alteraux.h"
#include "alterprevgraf.h"
#include "alterpagesofar.h"
#include "alterboxdimen.h"
#include "alterinteger.h"
#include "getnode.h"
#include "newpatterns.h"
#include "newhyphexceptions.h"
#include "findfontdimen.h"
#include "newfont.h"
#include "newinteraction.h"
#include "confusion.h"
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
			printnl("! ");
			print("You can't use a prefix with `");
			printcmdchr(curcmd, curchr);
			printchar('\''); 
			helpptr = 1;
			helpline[0] = "I'll pretend you didn't say \\long or \\outer or \\global.";
			backerror;
			return;
		}
	}
	if (curcmd != def && a%4)
	{
		printnl("! ");
		print("You can't use `");
		printesc("long");
		print("' or `");
		printesc("outer");
		print("' with `");
		printcmdchr(curcmd, curchr);
		printchar('\'');
		helpptr = 1;
		helpline[0] = "I'll pretend you didn't say \\long or \\outer here.";
		error();
	}
	if (int_par(global_defs_code))
		if (int_par(global_defs_code) < 0)
		{
			if (a >= 4)
				a -= 4;
		}
		else 
			if (a < 4)
			a += 4;
	switch (curcmd)
	{
		case set_font: 
			if (a >= 4)
				geqdefine(cur_font_loc, data, curchr);
			else
				eqdefine(cur_font_loc, data, curchr);
			break;
		case def:
			if (curchr%2 & a < 4 && int_par(global_defs_code) >= 0)
				a += 4;
			e = curchr >= 2;
			getrtoken();
			p = curcs;
			q = scantoks(true, e);
			if (a >= 4)
				geqdefine(p, 111+a%4, defref); // a%4 = 0:call 1:long_call 2:outer_call 3:long_outer_call
			else
				eqdefine(p, 111+a%4, defref); // a%4 = 0:call 1:long_call 2:outer_call 3:long_outer_call
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
			if (a >= 4)
				geqdefine(p, curcmd, curchr);
			else
				eqdefine(p, curcmd, curchr);
			break;
		case shorthand_def:
			n = curchr;
			getrtoken();
			p = curcs;
			if (a >= 4)
				geqdefine(p, relax, 256);
			else
				eqdefine(p, relax, 256);
			scanoptionalequals();
			switch (n)
			{
				case 0:
					scancharnum();
					if (a >= 4)
						geqdefine(p, char_given, curval);
					else
						eqdefine(p, char_given, curval);
					break;
				case 1:
					scanfifteenbitint();
					if (a >= 4)
						geqdefine(p, math_given, curval);
					else
						eqdefine(p, math_given, curval);
					break;
				default:
					scaneightbitint();
					switch (n)
					{
						case 2: 
							if (a >= 4)
								geqdefine(p, assign_int, count_base+curval);
							else
								eqdefine(p, assign_int, count_base+curval);
							break;
						case 3: 
							if (a >= 4)
								geqdefine(p, assign_dimen, scaled_base+curval);
							else
								eqdefine(p, assign_dimen, scaled_base+curval);
							break;
						case 4: 
							if (a >= 4)
								geqdefine(p, assign_glue, skip_base+curval);
							else
								eqdefine(p, assign_glue, skip_base+curval);
							break;
						case 5: 
							if (a >= 4)
								geqdefine(p, assign_mu_glue, mu_skip_base+curval);
							else
								eqdefine(p, assign_mu_glue, mu_skip_base+curval);
							break;
						case 6: 
							if (a >= 4)
								geqdefine(p, assign_toks, toks_base+curval);
							else
								eqdefine(p, assign_toks, toks_base+curval);
					}
			}
			break;
		case read_to_cs:
			scanint();
			n = curval;
			if (!scankeyword("to")) 
			{
				printnl("! ");
				print("Missing `to' inserted");
				helpptr = 2;
				helpline[1] = "You should have said `\\read<number> to \\cs'.";
				helpline[0] = "I'm going to look for the \\cs now.";
				error();
			}
			getrtoken();
			p = curcs;
			readtoks(n, p);
			if (a >= 4)
				geqdefine(p, call, curval);
			else
				eqdefine(p, call, curval);
			break;
		case toks_register:
		case assign_toks:
			q = curcs;
			if (curcmd == toks_register)
			{
				scaneightbitint();
				p = toks_base+curval;
			}
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
					scaneightbitint();
					curcmd = assign_toks;
					curchr = toks_base+curval;
				}
				if (curcmd == assign_toks)
				{
					q = equiv(curchr);
					if (q == 0)
						if (a >= 4)
							geqdefine(p, undefined_cs, 0);
						else
							eqdefine(p, undefined_cs, 0);
					else
					{
						info(q)++;
						if (a >= 4)
							geqdefine(p, call, q);
						else
							eqdefine(p, call, q);
					}
					break;
				}
			}
			backinput();
			curcs = q;
			q = scantoks(false, false);
			if (link(defref) == 0)
			{
				if (a >= 4)
					geqdefine(p, undefined_cs, 0);
				else
					eqdefine(p, undefined_cs, 0);
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
				if (a >= 4)
					geqdefine(p, call, defref);
				else
					eqdefine(p, call, defref);
			}
			break;
		case assign_int:
			p = curchr;
			scanoptionalequals();
			scanint();
			if (a >= 4)
				geqworddefine(p, curval);
			else
				eqworddefine(p, curval);
			break;
		case assign_dimen:
			p = curchr;
			scanoptionalequals();
			scandimen(false, false, false);
			if (a >= 4)
				geqworddefine(p, curval);
			else
				eqworddefine(p, curval);
			break;
		case assign_glue:
		case assign_mu_glue:
			p = curchr;
			n = curcmd;
			scanoptionalequals();
			if (n == 76)
				scanglue(3);
			else
				scanglue(2);
			trapzeroglue();
			if (a >= 4)
				geqdefine(p, glue_ref, curval);
			else
				eqdefine(p, glue_ref, curval);
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
			scancharnum();
			p += curval;
			scanoptionalequals();
			scanint();
			if ((curval < 0 && p < del_code_base) || curval > n)
			{
				printnl("! ");
				print("Invalid code (");
				printint(curval);
				if (p < del_code_base)
					print("), should be in the range 0..");
				else
					print("//), should be at most ");
				printint(n);
				helpptr = 1;
				helpline[0] = "I'm going to use 0 instead of that illegal code value.";
				error;
				curval = 0;
			}
			if (p < math_code_base)
				if (a >= 4)
					geqdefine(p, data, curval);
				else
					eqdefine(p, data, curval);
			else 
				if (p < del_code_base)
					if (a >= 4)
						geqdefine(p, data, curval);
					else
						eqdefine(p, data, curval);
				else 
					if (a >= 4)
						geqworddefine(p, curval);
					else
						eqworddefine(p, curval);
			break;
		case def_family:
			p = curchr;
			scanfourbitint();
			p += curval;
			scanoptionalequals();
			scanfontident();
			if (a >= 4)
				geqdefine(p, data, curval);
			else
				eqdefine(p, data, curval);
			break;
		case register_:
		case advance:
		case multiply:
		case divide: 
			doregistercommand(a);
			break;
		case set_box:
			scaneightbitint();
			if (a >= 4)
				n = 0x1'00+curval;
			else
				n = curval;
			scanoptionalequals();
			if (setboxallowed)
				scanbox(0x40'00'00'00+n);
			else
			{
				printnl("! ");
				print("Improper ");
				printesc("setbox");
				helpptr = 2;
				helpline[1] = "Sorry, \\setbox is not allowed after \\halign in a display,";
				helpline[0] = "or between \\accent and an accented character.";
				error();
			}
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
			scanint();
			n = curval;
			if (n <= 0)
				p = 0;
			else
			{
				p = getnode(2*n+1);
				info(p) = n;
				for (j = 1; j <= n; j++)
				{
					scandimen(false, false, false);
					mem[p+2*j-1].int_ = curval;
					scandimen(false, false, false);
					mem[p+2*j].int_ = curval;
				}
			}
			if (a >= 4)
				geqdefine(par_shape_loc, shape_ref, p);
			else
				eqdefine(par_shape_loc, shape_ref, p);
			break;
		case hyph_data:
			if (curchr == 1)
				newpatterns();
			else
				newhyphexceptions();
			break;
		case assign_font_dimen:
			findfontdimen(true);
			k = curval;
			scanoptionalequals();
			scandimen(false, false, false);
			fontinfo[k].int_ = curval;
			break;
		case assign_font_int:
			n = curchr;
			scanfontident();
			f = curval;
			scanoptionalequals();
			scanint();
			if (n == 0)
				hyphenchar[f] = curval;
			else
				skewchar[f] = curval;
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
