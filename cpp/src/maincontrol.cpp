#include "maincontrol.h"
#include "boite.h"
#include "equivalent.h" 
#include "police.h"
#include "cesure.h"
#include "getnext.h"
#include "fichier.h"
#include "erreur.h"
#include "sauvegarde.h"
#include "handlerightbrace.h"
#include "indentinhmode.h"
#include "normalparagraph.h"
#include "buildpage.h"
#include "itsallover.h"
#include "endgraf.h"
#include "begininsertoradjust.h"
#include "deletelast.h"
#include "makeaccent.h"
#include "alignement.h"
#include "initmath.h"
#include "starteqno.h"
#include "mathlimitswitch.h"
#include "lecture.h"
#include "etat.h"
#include "noeud.h"
#include "subsup.h"
#include "mathfraction.h"
#include "mathleftright.h"
#include "aftermath.h"
#include "prefixedcommand.h"
#include "issuemessage.h"
#include "impression.h"
#include "shiftcase.h"
#include "doextension.h"
#include "calcul.h"
#include "mainloop.h"
#include "initprim.h"

static void setmathchar(char status, int c, Token t)
{
	auto type = c>>12;
	if (type >= 8)
	{
		t.cs = t.chr+active_base;
		t.cmd = eqtb_active[t.cs].type;
		t.chr = eqtb_active[t.cs].int_;
		backinput(xtoken(status, t));
	}
	else
		tail_append(new Noad(c&0xFF, c >= var_code && fam_in_range() ? cur_fam() : (c&0xF00)>>8, type));
}

//! for mode-independent commands
#define ANY_MODE(cmd) vmode+cmd: case hmode+cmd: case mmode+cmd
//! for non-math commands
#define NON_MATH(cmd) vmode+cmd: case hmode+cmd

Token maincontrol(void)
{
	char status = normal;
	AlignRecordNode *loop = nullptr;
	if (every_job())
		beginTokenListAboveMacro(every_job(), every_job_text);
	auto t = getxtoken(status);
	while (true)
	{
		if (tracing_commands() > 0)
			showcurcmdchr(t);
		switch (abs(mode)+t.cmd)
		{
			case hmode+char_num:
				t.chr = scancharnum(status);
				[[fallthrough]];
			case hmode+letter:
			case hmode+other_char:
			case hmode+char_given:
				main_loop(status, t);
				continue;
			case hmode+no_boundary:
				t = getxtoken(status);
				if (t.cmd == letter || t.cmd == other_char || t.cmd == char_given || t.cmd == char_num)
					cancelboundary = true;
				continue;
			case hmode+spacer:
				if (space_factor != 1000)
				{
					appspace();
					break;
				}
				[[fallthrough]];
			case hmode+ex_space:
			case mmode+ex_space: 
				t = append_normal_space(status);
				continue;
			case ANY_MODE(relax):
			case vmode+spacer:
			case mmode+spacer:
			case mmode+no_boundary: 
				break;
			case ANY_MODE(ignore_spaces):
				t = getXTokenSkipSpace(status);
				continue;
			case vmode+stop:
				if (itsallover(status, t))
					return t;
				break;
			case vmode+vmove:
			case hmode+hmove:
			case mmode+hmove:
			case ANY_MODE(last_item):
			case vmode+vadjust:
			case vmode+ital_corr:
			case vmode+eq_no:
			case hmode+eq_no:
			case ANY_MODE(mac_param):
				reportillegalcase(t);
				break;
			case NON_MATH(sup_mark):
			case NON_MATH(sub_mark):
			case NON_MATH(math_char_num):
			case NON_MATH(math_given):
			case NON_MATH(math_comp):
			case NON_MATH(delim_num):
			case NON_MATH(left_right):
			case NON_MATH(above):
			case NON_MATH(radical):
			case NON_MATH(math_style):
			case NON_MATH(math_choice):
			case NON_MATH(vcenter):
			case NON_MATH(non_script):
			case NON_MATH(mkern):
			case NON_MATH(limit_switch):
			case NON_MATH(mskip):
			case NON_MATH(math_accent):
			case mmode+endv:
			case mmode+par_end:
			case mmode+stop:
			case mmode+vskip:
			case mmode+un_vbox:
			case mmode+valign:
			case mmode+hrule:
				backinput(t);
				t.tok = math_shift_token+'$';
				inserror(t, "Missing $ inserted", "I've inserted a begin-math/end-math symbol since I think\nyou left one out. Proceed, with fingers crossed.");
				break;
			case vmode+hrule:
			case hmode+vrule:
			case mmode+vrule:
				tail_append(scanrulespec(status, t));
				switch (abs(mode))
				{
					case vmode:
						prev_depth = ignore_depth;
						break;
					case hmode:
						space_factor = 1000;
				}
				break;
			case vmode+vskip:
			case hmode+hskip:
			case mmode+hskip:
			case mmode+mskip: 
				tail_append(glueToAppend(status, t.chr));
				break;
			case ANY_MODE(kern):
			case mmode+mkern: 
				tail_append(new KernNode(scandimen(status, t.chr == mu_glue, false, false), t.chr));
				break;
			case NON_MATH(left_brace):
				newsavelevel(simple_group);
				break;
			case ANY_MODE(begin_group):
				newsavelevel(semi_simple_group);
				break;
			case ANY_MODE(end_group):
				if (curgroup == semi_simple_group)
					unsave();
				else
					offsave(t);
				break;
			case ANY_MODE(right_brace):
				handlerightbrace(status, t, loop);
				break;
			case vmode+hmove:
			case hmode+vmove:
			case mmode+vmove:
				scanbox(status, t.chr == 0 ? scan_normal_dimen(status) : -scan_normal_dimen(status));
				break;
			case ANY_MODE(leader_ship):
				scanbox(status, leader_flag-a_leaders+t.chr);
				break;
			case ANY_MODE(make_box):
				beginbox(status, 0, t);
				break;
			case vmode+start_par: 
				newgraf(status, t.chr > 0);
				break;
			case vmode+letter:
			case vmode+other_char:
			case vmode+char_num:
			case vmode+char_given:
			case vmode+math_shift:
			case vmode+un_hbox:
			case vmode+vrule:
			case vmode+accent:
			case vmode+discretionary:
			case vmode+hskip:
			case vmode+valign:
			case vmode+ex_space:
			case vmode+no_boundary:
				backinput(t);
				newgraf(status, true);
				break;
			case hmode+start_par:
			case mmode+start_par: 
				indentinhmode(t);
				break;
			case vmode+par_end:
				normalparagraph();
				if (mode > 0)
					buildpage(status);
				break;
			case hmode+par_end:
				if (alignstate < 0)
					offsave(t);
				endgraf();
				if (mode == vmode)
					buildpage(status);
				break;
			case hmode+stop:
			case hmode+vskip:
			case hmode+un_vbox:
			case hmode+halign: 
				if (mode < 0)
					offsave(t);
				else
				{
					backinput(t);
					backinput(partoken);
					token_type = inserted;
				}
				break;
			case hmode+hrule:
				if (mode < 0)
					error("You can't use `"+esc("hrule")+"' here except with leaders", "To put a horizontal rule in an hbox or an alignment,\nyou should use \\leaders or \\hrulefill (see The TeXbook).");
				else
				{
					backinput(t);
					backinput(partoken);
					token_type = inserted;
				}
				break;
			case ANY_MODE(insert):
				beginInsert(status);
				break;
			case hmode+vadjust:
			case mmode+vadjust: 
				beginAdjust(status);
				break;
			case ANY_MODE(mark):
			{
				scanNonMacroToksExpand(status, t);
				tail_append(new MarkNode);
				break;
			}
			case ANY_MODE(break_penalty):
				tail_append(new PenaltyNode(scanint(status)));
				if (mode == vmode)
					buildpage(status);
				break;
			case ANY_MODE(remove_item):
				deletelast(t);
				break;
			case vmode+un_vbox:
			case hmode+un_hbox:
			case mmode+un_hbox: 
				unpackage(status, t.chr);
				break;
			case hmode+ital_corr: 
				appenditaliccorrection();
				break;
			case mmode+ital_corr:
				tail_append(new KernNode(0));
				break;
			case hmode+discretionary:
			case mmode+discretionary: 
				appenddiscretionary(status, t.chr);
				break;
			case hmode+accent: 
				makeaccent(status);
				break;
			case ANY_MODE(car_ret):
			case ANY_MODE(tab_mark):
				if (abs(alignstate) > 2)
				{
					if (t.tok == tab_token+'&')
						error("Misplaced "+cmdchr(t), "I can't figure out why you would want to use a tab mark\nhere. If you just want an ampersand, the remedy is\nsimple: Just type `I\\&' now. But if some right brace\nup above has ended a previous alignment prematurely,\nyou're probably due for more error messages, and you\nmight try typing `S' now just to see what is salvageable.");
					else
						error("Misplaced "+cmdchr(t), "I can't figure out why you would want to use a tab mark\nor \\cr or \\span just now. If something like a right brace\nup above has ended a previous alignment prematurely,\nyou're probably due for more error messages, and you\nmight try typing `S' now just to see what is salvageable.");
				}
				else
				{
					backinput(t);
					if (alignstate < 0)
					{
						inserror(t, "Missing { inserted", "I've put in what seems to be necessary to fix\nthe current column of the current alignment.\nTry to go on, since this might almost work.");
						alignstate++;
						t.tok = left_brace_token+'{'; 
					}
					else
					{
						inserror(t, "Missing } inserted", "I've put in what seems to be necessary to fix\nthe current column of the current alignment.\nTry to go on, since this might almost work.");
						alignstate--;
						t.tok = right_brace_token+ '}';
					}
				}
				break;
			case ANY_MODE(no_align):
				error("Misplaced "+esc("noalign"), "I expect to see \\noalign only after the \\cr of\nan alignment. Proceed, and I'll ignore this case.");
				break;
			case ANY_MODE(omit):
				error("Misplaced "+esc("omit"), "I expect to see \\omit only after tab marks or the \\cr of\nan alignment. Proceed, and I'll ignore this case.");
				break;
			case vmode+halign:
			case hmode+valign: 
				initalign(status, t, loop);
				break;
			case mmode+halign: 
				if (privileged(t))
					if (curgroup == math_shift_group)
						initalign(status, t, loop);
					else
						offsave(t);
				break;
			case vmode+endv:
			case hmode+endv: 
				doendv(status, t, loop);
				break;
			case ANY_MODE(end_cs_name):
				error("Extra "+esc("endcsname"), "I'm ignoring this, since I wasn't doing a \\csname.");
				break;
			case hmode+math_shift: 
				initmath(status);
				break;
			case mmode+eq_no: 
				if (privileged(t))
					if (curgroup == math_shift_group)
						starteqno(t);
					else
						offsave(t);
				break;
			case mmode+left_brace:
				tail_append(new Noad);
				backinput(t);
				dynamic_cast<Noad*>(tail)->nucleus.scan(status);
				break;
			case mmode+char_num:
				t.chr = scancharnum(status); [[fallthrough]];
			case mmode+letter:
			case mmode+other_char:
			case mmode+char_given: 
				setmathchar(status, math_code(t.chr), t);
				break;
			case mmode+math_char_num:
				setmathchar(status, scanfifteenbitint(status), t);
				break;
			case mmode+math_given: 
				setmathchar(status, t.chr, t);
				break;
			case mmode+delim_num:
				setmathchar(status, scantwentysevenbitint(status)>>12, t);
				break;
			case mmode+math_comp:
				tail_append(new Noad(t.chr));
				dynamic_cast<Noad*>(tail)->nucleus.scan(status);
				break;
			case mmode+limit_switch: 
				mathlimitswitch(t);
				break;
			case mmode+radical: 
				tail_append(new RadicalNoad(status, t));
				break;
			case mmode+accent:
				error("Please use "+esc("mathaccent")+" for accents in math mode", "I'm changing \\accent to \\mathaccent here; wish me luck.\n(Accents are not the same in formulas as they are in text.)");
				[[fallthrough]];
			case mmode+math_accent: 
				tail_append(new AccentNoad(status));
				break;
			case mmode+vcenter:
				t = scanspec(status, vcenter_group);
				normalparagraph();
				pushnest(); 
				mode = -vmode;
				prev_depth = ignore_depth;
				if (every_vbox())
					beginTokenListAboveMacro(every_vbox(), every_vbox_text);
				break;
			case mmode+math_style:
				tail_append(new StyleNode(t.chr));
				break;
			case mmode+non_script:
			{
				auto g = new GlueNode(zero_glue);
				g->subtype = cond_math_glue;
				tail_append(g);
				break;
			}
			case mmode+math_choice: 
				appendchoices(status);
				break;
			case mmode+sub_mark:
			case mmode+sup_mark: 
				subsup(status, t.cmd);
				break; 
			case mmode+above: 
				mathfraction(status, t.chr, t);
				break;
			case mmode+left_right: 
				(t.chr == left_noad ? mathleft : mathright)(status, t);
				break;
			case mmode+math_shift: 
				if (curgroup == math_shift_group)
					aftermath(status);
				else
					offsave(t);
				break;
			case ANY_MODE(toks_register):
			case ANY_MODE(assign_toks):
			case ANY_MODE(assign_int):
			case ANY_MODE(assign_dimen):
			case ANY_MODE(assign_glue):
			case ANY_MODE(assign_mu_glue):
			case ANY_MODE(assign_font_dimen):
			case ANY_MODE(assign_font_int):
			case ANY_MODE(set_aux):
			case ANY_MODE(set_prev_graf):
			case ANY_MODE(set_page_dimen):
			case ANY_MODE(set_page_int):
			case ANY_MODE(set_box_dimen):
			case ANY_MODE(set_shape):
			case ANY_MODE(def_code):
			case ANY_MODE(def_family):
			case ANY_MODE(set_font):
			case ANY_MODE(def_font):
			case ANY_MODE(register_):
			case ANY_MODE(advance):
			case ANY_MODE(multiply):
			case ANY_MODE(divide):
			case ANY_MODE(prefix):
			case ANY_MODE(let):
			case ANY_MODE(shorthand_def):
			case ANY_MODE(read_to_cs):
			case ANY_MODE(def):
			case ANY_MODE(set_box):
			case ANY_MODE(hyph_data):
			case ANY_MODE(set_interaction):
				prefixedcommand(status, t);
				break;
			case ANY_MODE(after_assignment):
				aftertoken = t = gettoken(status);
				break;
			case ANY_MODE(after_group):
				t = gettoken(status);
				saveforafter(t.tok);
				break;
			case ANY_MODE(in_stream):
				openorclosein(status, t.chr);
				break;
			case ANY_MODE(message):
				issuemessage(status, t);
				break;
			case ANY_MODE(case_shift):
				shiftcase(status, t);
				break;
			case ANY_MODE(xray):
				showwhatever(status, t);
				break;
			case ANY_MODE(extension):
				doextension(status, t);
		}
		t = getxtoken(status);
	}
}
