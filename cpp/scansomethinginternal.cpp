#include "scansomethinginternal.h"
#include "scancharnum.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "scaneightbitint.h"
#include "backinput.h"
#include "scanfontident.h"
#include "findfontdimen.h"
#include "printcmdchr.h"
#include "printesc.h"
#include "error.h"
#include "muerror.h"
#include "newspec.h"
#include "texte.h"

static halfword& mu_skip(halfword p) { return equiv(mu_skip_base+p); }

void scansomethinginternal(smallnumber level, bool negative)
{
	halfword m = curchr;
	switch (curcmd)
	{
		case def_code:
			scancharnum();
			if (m == math_code_base)
				scanned_result(math_code(curval), int_val);
			else 
				if (m < math_code_base)
					scanned_result(equiv(m+curval), int_val);
				else
					scanned_result(eqtb[m+curval].int_, int_val);
			break;
		case toks_register:
		case assign_toks:
		case def_family:
		case set_font:
		case def_font:
			if (level != tok_val)
			{
				printnl("! ");
				print("Missing number, treated as zero");
				helpptr = 3;
				helpline[2] = "A number should have been here; I inserted `0'.";
				helpline[1] = "(If you can't figure out why I needed to see a number,";
				helpline[0] = "look up `weird error' in the index to The TeXbook.)";
				backerror();
				scanned_result(0, dimen_val);
			}
			else 
				if (curcmd <= assign_toks)
				{
					if (curcmd < assign_toks)
					{
						scaneightbitint;
						m = toks_base+curval;
					}
					scanned_result(equiv(m), tok_val);
				}
				else
				{
					backinput();
					scanfontident();
					scanned_result(curval+frozen_null_font, ident_val);
				}
			break;
		case assign_int:
			scanned_result(eqtb[m].int_, int_val);
			break;
		case assign_dimen:
			scanned_result(eqtb[m].int_, dimen_val);
			break;
		case assign_glue:
			scanned_result(equiv(m), glue_val);
			break;
		case assign_mu_glue:
			scanned_result(equiv(m), mu_val);
			break;
		case set_aux:
			if (abs(mode) != m)
			{
				printnl("! ");
				print("Improper ");
				printcmdchr(set_aux, m);
				helpptr = 4;
				helpline[3] = "You can refer to \\spacefactor only in horizontal mode;";
				helpline[2] = "you can refer to \\prevdepth only in vertical mode; and";
				helpline[1] = "neither of these is meaningful inside \\write. So";
				helpline[0] = "I'm forgetting what you said and using zero instead.";
				error();
				if (level != tok_val)
					scanned_result(0, dimen_val);
				else
					scanned_result(0, int_val);
			}
			else 
				if (m == 1)
					scanned_result(prev_depth, dimen_val);
				else
					scanned_result(space_factor, int_val);
			break;
		case set_prev_graf:
			if (mode == 0)
				scanned_result(0, int_val);
			else
			{
				nest[nestptr] = curlist;
				auto p = nestptr;
				while (abs(nest[p].modefield) != vmode)
					p--;
				scanned_result(nest[p].pgfield, int_val);
			}
			break;
		case set_page_int:
			if (m == 0)
				scanned_result(deadcycles, int_val);
			else
				scanned_result(insertpenalties, int_val);
			break;
		case set_page_dimen:
			if (pagecontents == 0 && !outputactive)
				if (m == 0)
					scanned_result(max_dimen, dimen_val);
				else
					scanned_result(0, dimen_val);
			else
				scanned_result(pagesofar[m], dimen_val);
			break;
		case set_shape:
			if (par_shape_ptr() == 0)
				scanned_result(0, int_val);
			else
				scanned_result(info(par_shape_ptr()), int_val);
			break;
		case set_box_dimen:
			scaneightbitint();
			if (box(curval) == 0)
				scanned_result(0, 1);
			else
				scanned_result(mem[box(curval)+m].int_, dimen_val);
		break;
		case char_given:
		case math_given:
			scanned_result(curchr, 0);
			break;
		case assign_font_dimen:
			findfontdimen(false);
			fontinfo[fmemptr].int_ = 0;
			scanned_result(fontinfo[curval].int_, dimen_val);
			break;
		case assign_font_int:
			scanfontident();
			if (m == 0)
				scanned_result(hyphenchar[curval], int_val);
			else
			{
				scanned_result(skewchar[curval], int_val);
			};
			break;
		case register_:
			scaneightbitint();
			switch (m)
			{
				case int_val: 
					scanned_result(count(curval), m);
					break;
				case dimen_val: 
					scanned_result(dimen(curval), m);
					break;
				case glue_val: 
					scanned_result(skip(curval), m);
					break;
				case mu_val: 
					scanned_result(mu_skip(curval), m);
			};
			break;
		case last_item:
			if (curchr > glue_val)
				if (curchr == input_line_no_code)
					scanned_result(line, 0);
				else
					scanned_result(lastbadness, int_val);
			else
			{
				 if (curchr == glue_val)
					scanned_result(zero_glue, curchr);
				  else
					scanned_result(0, curchr);
				if (!is_char_node(tail) && mode)
					switch (curchr)
					{
						case int_val: 
							if (type(tail) == penalty_node)
								curval = penalty(tail);
							break;
						case dimen_val: 
							if (type(tail) == kern_node)
								curval = width(tail);
							break;
						case glue_val: 
							if (type(tail) == glue_node)
							{
								curval = glue_ptr(tail);
								if (subtype(tail) == mu_glue)
									curvallevel = mu_val;
							}
					}
				else 
					if (mode == vmode && tail == head)
						switch (curchr)
						{
							case int_val: 
								curval = lastpenalty;
								break;
							case dimen_val: 
								curval = lastkern;
								break;
							case glue_val: 
								if (lastglue != empty_flag)
									curval = lastglue;
						}
			}
			break;
		default:
			printnl("! ");
			print("You can't use `");
			printcmdchr(curcmd, curchr);
			print("' after ");
			printesc("the");
			helpptr = 1;
			helpline[0] = "I'm forgetting what you said and using zero instead.";
			error();
			if (level != tok_val)
				scanned_result(0, dimen_val);
			else
				scanned_result(0, int_val);
	};
	while (curvallevel > level)
	{
		if (curvallevel == glue_val)
			curval = width(curval);
		else 
			if (curvallevel == mu_val)
			muerror();
		curvallevel--;
	}
	if (negative)
		if (curvallevel >= glue_val)
		{
			curval = newspec(curval);
			width(curval) = -width(curval);
			stretch(curval) = -stretch(curval);
			shrink(curval) = -shrink(curval);
		}
		else
			curval = -curval;
	else 
		if (curvallevel >= glue_val && curvallevel <= mu_val)
			add_glue_ref(curval);
}
