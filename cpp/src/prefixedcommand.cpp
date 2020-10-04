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
		auto c = t.chr;
		scanoptionalequals();
		if (c == vmode)
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
	if (global_defs() < 0 && a >= 4)
		a -= 4;
	if (global_defs() > 0 && a < 4)
		a += 4;
	int val;
	fontindex k;
	int n;
	switch (t.cmd)
	{
		case set_font:
			define(a, &eqtb_local[cur_font_loc-local_base], data, t.chr);
			break;
		case def:
		{
			if (t.chr%2 & a < 4 && global_defs() >= 0)
				a += 4;
			auto p = getrtoken();
			Token tk;
			tk.cs = p;
			scanMacroToks(t.chr >= 2, tk);
			define_(a, &eqtb_cs[p-hash_base], call+a%4, &defRef); // a%4 = 0:call 1:long_call 2:outer_call 3:long_outer_call
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
			define(a, &eqtb_cs[p-hash_base], t.cmd, t.chr);
			break;
		}
		case shorthand_def:
		{
			auto p = getrtoken();
			define(a, &eqtb_cs[p-hash_base], relax, 256);
			scanoptionalequals();
			switch (t.chr)
			{
				case char_def_code:
					define(a, &eqtb_cs[p-hash_base], char_given, scancharnum());
					break;
				case math_char_def_code:
					define(a, &eqtb_cs[p-hash_base], math_given, scanfifteenbitint());
					break;
				case count_def_code: 
					define(a, &eqtb_cs[p-hash_base], assign_int, count_base+scaneightbitint());
					break;
				case dimen_def_code: 
					define(a, &eqtb_cs[p-hash_base], assign_dimen, scaled_base+scaneightbitint());
					break;
				case skip_def_code:
					define(a, &eqtb_cs[p-hash_base], assign_glue, skip_base+scaneightbitint());
					break;
				case mu_skip_def_code: 
					define(a, &eqtb_cs[p-hash_base], assign_mu_glue, mu_skip_base+scaneightbitint());
					break;
				case toks_def_code: 
					define(a, &eqtb_cs[p-hash_base], assign_toks, toks_base+scaneightbitint());
			}
			break;
		}
		case read_to_cs:
		{
			n = scanint();
			if (!scankeyword("to")) 
				error("Missing `to' inserted", "You should have said `\\read<number> to \\cs'.\nI'm going to look for the \\cs now.");
			auto p = getrtoken();
			define_(a, &eqtb_cs[p-hash_base], call, readtoks(n, p));
			break;
		}
		case toks_register:
		case assign_toks:
		{
			auto old = t.cs;
			auto p = t.cmd == toks_register ? toks_base+scaneightbitint() : t.chr;
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
					if (auto q = dynamic_cast<TokenList*>(eqtb_local[t.chr-local_base].index); q == nullptr)
						define_(a, &eqtb_local[p-local_base], undefined_cs, nullptr);
					else
					{
						q->token_ref_count++;
						define_(a, &eqtb_local[p-local_base], call, q);
					}
					break;
				}
			}
			backinput(t);
			Token tk;
			tk.cs = old;
			scanNonMacroToks(tk);
			if (defRef.list.size() == 0)
			{
				define_(a, &eqtb_local[p-local_base], undefined_cs, nullptr);
				defRef.token_ref_count = 0;
			}
			else
			{
				if (p == output_routine_loc) 
				{
					defRef.list.insert(defRef.list.begin(), left_brace_token+'{');
					defRef.list.push_back(right_brace_token+'}');
				}
				define_(a, &eqtb_local[p-local_base], call, &defRef);
			}
			break;
		}
		case assign_int:
		{
			auto p = t.chr;
			scanoptionalequals();
			word_define(a, &eqtb_int[p-int_base], scanint());
			break;
		}
		case assign_dimen:
		{
			auto p = t.chr;
			scanoptionalequals();
			word_define(a, &eqtb_dimen[p-dimen_base], scandimen(false, false, false));
			break;
		}
		case assign_glue:
		case assign_mu_glue:
		{
			auto p = t.chr;
			n = t.cmd;
			scanoptionalequals();
			auto g = trapzeroglue(scanglue(n == assign_mu_glue ? mu_val : glue_val));
			define_(a, &eqtb_glue[p-glue_base], glue_ref, g);
			break;
		}
		case def_code:
		{
			switch (t.chr)
			{
				case cat_code_base:
					n = (1<<4)-1;
					break;
				case math_code_base:
					n = 1<<15;
					break;
				case sf_code_base:
					n = (1<<15)-1;
					break;
				case del_code_base:
					n = (1<<24)-1;
					break;
				default:
					n = (1<<8)-1;
			}
			auto p = t.chr+scancharnum();
			scanoptionalequals();
			val = scanint();
			if ((val < 0 && p < del_code_base) || val > n)
			{
				error("Invalid code ("+std::to_string(val)+(p < del_code_base ? "), should be in the range 0.." : "//), should be at most ")+std::to_string(n), "I'm going to use 0 instead of that illegal code value.");
				val = 0;
			}
			if (p < math_code_base)
				define(a, &eqtb_local[p-local_base], data, val);
			else 
				if (p < del_code_base)
					define(a, &eqtb_local[p-local_base], data, val);
				else 
					word_define(a, &eqtb_int[p-int_base], val);
			break;
		}
		case def_family:
		{	
			auto p = t.chr+scanfourbitint();
			scanoptionalequals();
			define(a, &eqtb_local[p-local_base], data, scanfontident());
			break;
		}
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
			n = scanint();
			auto p = n <= 0 ? nullptr : new ShapeNode(n);
			for (int j = 0; j < 2*n; j++)
				p->values.push_back(scan_normal_dimen());
			define_(a, &eqtb_local[par_shape_loc-local_base], shape_ref, p);
			break;
		}
		case hyph_data:
			if (t.chr == 1)
				newpatterns(t);
			else
				newhyphexceptions();
			break;
		case assign_font_dimen:
			k = findfontdimen(true);
			scanoptionalequals();
			Font::info[k].int_ = scan_normal_dimen();
			break;
		case assign_font_int:
		{
			n = t.chr;
			auto f = scanfontident();
			scanoptionalequals();
			(n == 0 ? fonts[f].hyphenchar : fonts[f].skewchar) = scanint();
			break;
		}
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
