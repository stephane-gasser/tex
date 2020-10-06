#include "prefixedcommand.h"
#include "impression.h"
#include "erreur.h"
#include "equivalent.h"
#include "backinput.h"
#include "trapzeroglue.h"
#include "doregistercommand.h"
#include "lecture.h"
#include "noeud.h"
#include "cesure.h"
#include "police.h"
#include "boite.h"
#include "buildpage.h"

static void alterprevgraf(void)
{
	nest.back() = curlist;
	auto p = nest.size()-1;
	while (abs(nest[p].modefield) != vmode)
		p--;
	scanoptionalequals();
	int val = scanint();
	if (val < 0)
		interror(val, " Bad "+esc("prevgraf"), "I allow only nonnegative values here.");
	else
	{
		nest[p].pgfield = val;
		curlist = nest.back();
	}
}

static void alteraux(Token t)
{
	if (t.chr != abs(mode))
		reportillegalcase(t);
	else
	{
		scanoptionalequals();
		if (t.chr == vmode)
			prev_depth = scan_normal_dimen();
		else
		{
			int val = scanint();
			if (val <= 0 || val > 32767)
				interror(val, "Bad space factor", "I allow only values in the range 1..32767 here.");
			else
				space_factor = val;
		}
	}
}

void prefixedcommand(Token t, bool setboxallowed) 
{
	smallnumber pfx = noPrefix;
	while (t.cmd == prefix)
	{
		if (pfx&t.chr == 0)
			pfx += t.chr;
		t = getXTokenSkipSpaceAndEscape();
		if (t.cmd <= max_non_prefixed_command)
		{
			backerror(t, "You can't use a prefix with `"+cmdchr(t)+"\'", "I'll pretend you didn't say \\long or \\outer or \\global.");
			return;
		}
	}
	if (t.cmd != def && pfx%globalPrefix)
		error("You can't use `"+esc("long")+"' or `"+esc("outer")+"' with `"+cmdchr(t)+"\'", "I'll pretend you didn't say \\long or \\outer here.");
	if (global_defs() < 0 && pfx >= globalPrefix)
		pfx -= globalPrefix;
	if (global_defs() > 0 && pfx < globalPrefix)
		pfx += globalPrefix;
	int val;
	switch (t.cmd)
	{
		case set_font:
			eqtb_local[cur_font_loc-local_base].define(pfx, data, t.chr);
			break;
		case def:
		{
			if ((t.chr&longPrefix) && pfx < globalPrefix && global_defs() >= 0)
				pfx += globalPrefix;
			auto p = getrtoken();
			Token tk;
			tk.cs = p;
			scanMacroToks(t.chr >= 2, tk);
			eqtb_cs[p-hash_base].define(pfx, call+pfx%globalPrefix, &defRef); // pfx%globalPrefix = 0:call 1:long_call 2:outer_call 3:long_outer_call
			break;
		}
		case let:
		{
			auto p = getrtoken();
			if (t.chr == 0)
			{
				t = getXTokenSkipSpace();
				if (t.tok == other_token+'=')
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
				dynamic_cast<TokenList*>(eqtb_cs[t.chr-hash_base].index)->token_ref_count++;
			eqtb_cs[p-hash_base].define(pfx, t.cmd, t.chr);
			break;
		}
		case shorthand_def:
		{
			auto p = getrtoken();
			eqtb_cs[p-hash_base].define(pfx, relax, 256);
			scanoptionalequals();
			switch (t.chr)
			{
				case char_def_code:
					eqtb_cs[p-hash_base].define(pfx, char_given, scancharnum());
					break;
				case math_char_def_code:
					eqtb_cs[p-hash_base].define(pfx, math_given, scanfifteenbitint());
					break;
				case count_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_int, count_base+scaneightbitint());
					break;
				case dimen_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_dimen, scaled_base+scaneightbitint());
					break;
				case skip_def_code:
					eqtb_cs[p-hash_base].define(pfx, assign_glue, skip_base+scaneightbitint());
					break;
				case mu_skip_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_mu_glue, mu_skip_base+scaneightbitint());
					break;
				case toks_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_toks, toks_base+scaneightbitint());
			}
			break;
		}
		case read_to_cs:
		{
			auto n = scanint();
			if (!scankeyword("to")) 
				error("Missing `to' inserted", "You should have said `\\read<number> to \\cs'.\nI'm going to look for the \\cs now.");
			auto p = getrtoken();
			eqtb_cs[p-hash_base].define(pfx, call, readtoks(n, p));
			break;
		}
		case toks_register:
		case assign_toks:
		{
			auto old = t.cs;
			auto p = t.cmd == toks_register ? toks_base+scaneightbitint() : t.chr;
			scanoptionalequals();
			t = getXTokenSkipSpaceAndEscape();
			if (t.cmd == toks_register)
				t = Token(assign_toks, toks_base+scaneightbitint());
			if (t.cmd == assign_toks)
			{
				if (eqtb_local[t.chr-local_base].index == nullptr)
					eqtb_local[p-local_base].define(pfx, undefined_cs, nullptr);
				else
				{
					auto q = dynamic_cast<TokenList*>(eqtb_local[t.chr-local_base].index);
					q->token_ref_count++;
					eqtb_local[p-local_base].define(pfx, call, q);
				}
				break;
			}
			backinput(t);
			Token tk;
			tk.cs = old;
			scanNonMacroToks(tk);
			if (defRef.list.size() == 0)
			{
				eqtb_local[p-local_base].define(pfx, undefined_cs, nullptr);
				defRef.token_ref_count = 0;
			}
			else
			{
				if (p == output_routine_loc) 
				{
					defRef.list.insert(defRef.list.begin(), left_brace_token+'{');
					defRef.list.push_back(right_brace_token+'}');
				}
				eqtb_local[p-local_base].define(pfx, call, &defRef);
			}
			break;
		}
		case assign_int:
		{
			auto p = t.chr;
			scanoptionalequals();
			eqtb_int[p-int_base].word_define(pfx, scanint());
			break;
		}
		case assign_dimen:
		{
			auto p = t.chr;
			scanoptionalequals();
			eqtb_dimen[p-dimen_base].word_define(pfx, scandimen(false, false, false));
			break;
		}
		case assign_glue:
		case assign_mu_glue:
		{
			scanoptionalequals();
			auto g = trapzeroglue(scanglue(t.cmd == assign_mu_glue ? mu_val : glue_val));
			eqtb_glue[t.chr-glue_base].define(pfx, glue_ref, g);
			break;
		}
		case def_code:
		{
			int maxValue = (1<<8)-1; // \lccode / \uccode
			switch (t.chr)
			{
				case cat_code_base: // \catcode
					maxValue = (1<<4)-1;
					break;
				case math_code_base: // \mathcode
					maxValue = 1<<15;
					break;
				case sf_code_base: // \sfcode
					maxValue = (1<<15)-1;
					break;
				case del_code_base: // \delcode
					maxValue = (1<<24)-1;
			}
			auto p = t.chr+scancharnum();
			scanoptionalequals();
			val = scanint();
			if ((val < 0 && t.chr != del_code_base) || val > maxValue)
			{
				error("Invalid code ("+std::to_string(val)+(t.chr != del_code_base ? "), should be in the range 0.." : "//), should be at most ")+std::to_string(maxValue), "I'm going to use 0 instead of that illegal code value.");
				val = 0;
			}
			if (t.chr == del_code_base)
				eqtb_int[p-int_base].word_define(pfx, val);
			else
				eqtb_local[p-local_base].define(pfx, data, val);
			break;
		}
		case def_family:
		{	
			auto p = t.chr+scanfourbitint();
			scanoptionalequals();
			eqtb_local[p-local_base].define(pfx, data, scanfontident());
			break;
		}
		case register_:
		case advance:
		case multiply:
		case divide: 
			doregistercommand(pfx, t);
			break;
		case set_box:
		{
			auto n = scaneightbitint();
			if (pfx >= globalPrefix)
				n += 1<<8;
			scanoptionalequals();
			if (setboxallowed)
				scanbox(box_flag+n);
			else
				error("Improper "+esc("setbox"), "Sorry, \\setbox is not allowed after \\halign in a display,\nor between \\accent and an accented character.");
			break;
		}
		case set_aux: 
			alteraux(t);
			break;
		case set_prev_graf: 
			alterprevgraf();
			break;
		case set_page_dimen: 
			scanoptionalequals();
			pagesofar[t.chr] = scan_normal_dimen();
			break;
		case set_page_int: 
			scanoptionalequals();
			(t.chr == 0 ? deadcycles : insertpenalties) = scanint();
			break;
		case set_box_dimen: 
			alterboxdimen(t.chr);
			break;
		case set_shape:
		{
			scanoptionalequals();
			auto n = scanint();
			eqtb_local[par_shape_loc-local_base].define(pfx, shape_ref, n <= 0 ? nullptr : new ShapeNode(n));
			break;
		}
		case hyph_data:
			if (t.chr == 1)
				newpatterns(t);
			else
				newhyphexceptions();
			break;
		case assign_font_dimen:
		{
			fontindex k;
			k = findfontdimen(true);
			scanoptionalequals();
			Font::info[k].int_ = scan_normal_dimen();
			break;
		}
		case assign_font_int:
		{
			auto f = scanfontident();
			scanoptionalequals();
			(t.chr == 0 ? fonts[f].hyphenchar : fonts[f].skewchar) = scanint();
			break;
		}
		case def_font: 
			newfont(pfx);
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
