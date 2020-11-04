#include "prefixedcommand.h"
#include "impression.h"
#include "erreur.h"
#include "equivalent.h"
#include "etat.h"
#include "doregistercommand.h"
#include "lecture.h"
#include "noeud.h"
#include "cesure.h"
#include "police.h"
#include "boite.h"
#include "buildpage.h"
#include "getnext.h"
#include "alignement.h"
#include "fichier.h"

static TokenList* readtoks(int n, halfword r)
{
	warningindex = r;
	defRef = TokenList(end_match_token);
	smallnumber m = between(0, n, 15) ? n : 16;
	auto s = alignstate;
	alignstate = 1000000;
	do
	{
		beginfilereading();
		name = m+1;
		switch (readopen[m])
		{
			case closed:
				if (interaction > nonstop_mode)
				{
					if (n >= 0)
					print("\n"+scs(r)+"=");
					n = -1;
					terminput();
				}
				else
					fatalerror("*** (cannot \read from terminal in nonstop modes)");
				break;
			case just_open:
				readopen[m] = inputln(readfile[m], false) ? opened : closed;
				if (readopen[m] == closed)
					aclose(readfile[m]);
				break;
			default: // opened
				readopen[m] = inputln(readfile[m], true) ? opened : closed;
				if (readopen[m] == closed)
				{
					aclose(readfile[m]);
					if (alignstate != 1000000)
					{
						print("\rRunaway definition?\n"+defRef.toString(errorline-10));
						error("File ended within "+esc("read"), "This \\read has unbalanced braces.");
						alignstate = 1000000;
					}
				}
		}
		limit = last;
		if (end_line_char_inactive())
			limit--;
		else
			buffer[limit] = end_line_char();
		First = limit+1;
		Loc = 0/*Start*/;
		state = new_line;
		for (auto t = scanner.get(defining); t.tok; t = scanner.get(defining))
			if (alignstate >= 1000000)
				defRef.list.push_back(t.tok);
			else
			{
				do
					t = scanner.get(defining);
				while (t.tok);
				alignstate = 1000000;
				break;
			}
		endfilereading();
	} while (alignstate != 1000000);
	alignstate = s;
	return &defRef;
}

static void alterprevgraf(char status)
{
	nest.back() = curlist;
	auto p = nest.size()-1;
	while (abs(nest[p].modefield) != vmode)
		p--;
	scanner.optionalEquals(status);
	if (int val = scanner.getInt(status); val < 0)
		interror(val, " Bad "+esc("prevgraf"), "I allow only nonnegative values here.");
	else
	{
		nest[p].pgfield = val;
		curlist = nest.back();
	}
}

static void alteraux(char status, Token t)
{
	if (t.chr != abs(mode))
	{
		reportillegalcase(t);
		return;
	}
	scanner.optionalEquals(status);
	if (t.chr == vmode)
	{
		prev_depth = scanner.getNormalDimen(status);
		return;
	}
	if (int val = scanner.getInt(status); between(1, val, 32767))
		space_factor = val;
	else
		interror(val, "Bad space factor", "I allow only values in the range 1..32767 here.");
}

static smallnumber getPrefix(char status, Token t)
{
	smallnumber pfx = noPrefix;
	while (t.cmd == prefix)
	{
		if (pfx&t.chr == 0)
			pfx += t.chr;
		t = scanner.getXSkipSpaceAndEscape(status);
		if (t.cmd <= max_non_prefixed_command)
		{
			backerror(t, "You can't use a prefix with `"+t.cmdchr()+"\'", "I'll pretend you didn't say \\long or \\outer or \\global.");
			throw;
		}
	}
	if (t.cmd != def && pfx%globalPrefix)
		error("You can't use `"+esc("long")+"' or `"+esc("outer")+"' with `"+t.cmdchr()+"\'", "I'll pretend you didn't say \\long or \\outer here.");
	if (global_defs() < 0 && pfx >= globalPrefix)
		pfx -= globalPrefix;
	if (global_defs() > 0 && pfx < globalPrefix)
		pfx += globalPrefix;
	return pfx;
}

static void afterPrefixedCommand(Token &aftertoken)
{
	if (aftertoken.tok)
	{
		backinput(aftertoken);
		aftertoken.tok = 0;
	}
}

void prefixedcommand(char &status, Token t, bool setboxallowed) 
{
	smallnumber pfx;
	try { pfx = getPrefix(status, t); } 
	catch (...) { return; }
	switch (t.cmd)
	{
		case set_font:
			eqtb_local[cur_font_loc-local_base].define(pfx, data, t.chr);
			break;
		case def:
		{
			if ((t.chr&longPrefix) && pfx < globalPrefix && global_defs() >= 0)
				pfx += globalPrefix;
			auto p = scanner.getR(status);
			scanMacroToks(t.chr >= 2, p+cs_token_flag);
			status = normal;
			eqtb_cs[p-hash_base].define(pfx, call+pfx%globalPrefix, &defRef); // pfx%globalPrefix = 0:call 1:long_call 2:outer_call 3:long_outer_call
			break;
		}
		case let:
		{
			auto p = scanner.getR(status);
			if (t.chr == 0)
			{
				t = scanner.getXSkipSpace(status);
				if (t.tok == other_token+'=')
				{
					t = scanner.get(status);
					if (t.cmd == spacer)
						t = scanner.get(status);
				}
			}
			else
			{
				auto tt = scanner.get(status);
				t = scanner.get(status);
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
			auto p = scanner.getR(status);
			eqtb_cs[p-hash_base].define(pfx, relax, 256);
			scanner.optionalEquals(status);
			switch (t.chr)
			{
				case char_def_code:
					eqtb_cs[p-hash_base].define(pfx, char_given, scanner.getUChar(status));
					break;
				case math_char_def_code:
					eqtb_cs[p-hash_base].define(pfx, math_given, scanner.getUInt15(status));
					break;
				case count_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_int, count_base+scanner.getUInt8(status));
					break;
				case dimen_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_dimen, scaled_base+scanner.getUInt8(status));
					break;
				case skip_def_code:
					eqtb_cs[p-hash_base].define(pfx, assign_glue, skip_base+scanner.getUInt8(status));
					break;
				case mu_skip_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_mu_glue, mu_skip_base+scanner.getUInt8(status));
					break;
				case toks_def_code: 
					eqtb_cs[p-hash_base].define(pfx, assign_toks, toks_base+scanner.getUInt8(status));
			}
			break;
		}
		case read_to_cs:
		{
			auto n = scanner.getInt(status);
			if (!scanner.isKeyword(status, "to")) 
				error("Missing `to' inserted", "You should have said `\\read<number> to \\cs'.\nI'm going to look for the \\cs now.");
			auto p = scanner.getR(status);
			eqtb_cs[p-hash_base].define(pfx, call, readtoks(n, p));
			status = normal;
			break;
		}
		case toks_register:
		{
			auto p = toks_base+scanner.getUInt8(status);
			scanner.optionalEquals(status);
			scanner.getXSkipSpaceAndEscape(status);
			backinput(Token(assign_toks, toks_base+scanner.getUInt8(status)));
			scanNonMacroToks(t.cs+cs_token_flag);
			status = normal;
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
		case assign_toks:
			scanner.optionalEquals(status);
			t = scanner.getXSkipSpaceAndEscape(status);
			if (eqtb_local[t.chr-local_base].index == nullptr)
				eqtb_local[t.chr-local_base].define(pfx, undefined_cs, nullptr);
			else
			{
				auto q = dynamic_cast<TokenList*>(eqtb_local[t.chr-local_base].index);
				q->token_ref_count++;
				eqtb_local[t.chr-local_base].define(pfx, call, q);
			}
			break;
		case assign_int:
			scanner.optionalEquals(status);
			eqtb_int[t.chr-int_base].word_define(pfx, scanner.getInt(status));
			break;
		case assign_dimen:
			scanner.optionalEquals(status);
			eqtb_dimen[t.chr-dimen_base].word_define(pfx, scanner.getDimen(status, false, false));
			break;
		case assign_glue:
		case assign_mu_glue:
		{
			scanner.optionalEquals(status);
			auto g = trapzeroglue(scanner.getGlue(status, t.cmd == assign_mu_glue ? mu_val : glue_val));
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
			auto p = t.chr+scanner.getUChar(status);
			scanner.optionalEquals(status);
			auto val = scanner.getInt(status);
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
			auto p = t.chr+scanner.getUInt4(status);
			scanner.optionalEquals(status);
			eqtb_local[p-local_base].define(pfx, data, scanner.getFontIdent(status));
			break;
		}
		case register_:
		case advance:
		case multiply:
		case divide: 
			doregistercommand(status, pfx, t);
			break;
		case set_box:
		{
			auto n = scanner.getUInt8(status);
			if (pfx >= globalPrefix)
				n += 1<<8;
			scanner.optionalEquals(status);
			if (setboxallowed)
				scanner.getBox(status, box_flag+n);
			else
				error("Improper "+esc("setbox"), "Sorry, \\setbox is not allowed after \\halign in a display,\nor between \\accent and an accented character.");
			break;
		}
		case set_aux:
			alteraux(status, t);
			break;
		case set_prev_graf: 
			alterprevgraf(status);
			break;
		case set_page_dimen: 
			scanner.optionalEquals(status);
			pagesofar[t.chr] = scanner.getNormalDimen(status);
			break;
		case set_page_int: 
			scanner.optionalEquals(status);
			(t.chr == 0 ? deadcycles : insertpenalties) = scanner.getInt(status);
			break;
		case set_box_dimen: 
			alterboxdimen(status, t.chr);
			break;
		case set_shape:
		{
			scanner.optionalEquals(status);
			auto n = scanner.getInt(status);
			eqtb_local[par_shape_loc-local_base].define(pfx, shape_ref, n <= 0 ? nullptr : new ShapeNode(status, n));
			break;
		}
		case hyph_data:
			if (t.chr == 1)
			{
				if (trienotready)
				{
					newpatterns(status, t);
					break;
				}
				error("Too late for "+esc("patterns"), "All patterns must be given before typesetting begins.");
				scanNonMacroToks(t);
				defRef.list.clear();
				status = normal;
			}
			else
				newhyphexceptions(status);
			break;
		case assign_font_dimen:
		{
			fontindex k;
			k = findfontdimen(status, true);
			scanner.optionalEquals(status);
			Font::info[k].int_ = scanner.getNormalDimen(status);
			break;
		}
		case assign_font_int:
		{
			auto f = scanner.getFontIdent(status);
			scanner.optionalEquals(status);
			(t.chr == 0 ? fonts[f].hyphenchar : fonts[f].skewchar) = scanner.getInt(status);
			break;
		}
		case def_font: 
			newfont(status, pfx);
			break;
		case set_interaction: 
			newinteraction(t);
			break;
		default: 
			confusion("prefix");
	}
	afterPrefixedCommand(aftertoken);
}
