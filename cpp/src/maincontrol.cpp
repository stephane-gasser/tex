#include "maincontrol.h"
#include "boite.h"
#include "equivalent.h" 
#include "police.h"
#include "cesure.h"
#include "fixlanguage.h"
#include "getnext.h"
#include "charwarning.h"
#include "backinput.h"
#include "erreur.h"
#include "insertdollarsign.h"
#include "sauvegarde.h"
#include "offsave.h"
#include "handlerightbrace.h"
#include "indentinhmode.h"
#include "normalparagraph.h"
#include "buildpage.h"
#include "headforvmode.h"
#include "itsallover.h"
#include "endgraf.h"
#include "begininsertoradjust.h"
#include "makemark.h"
#include "deletelast.h"
#include "makeaccent.h"
#include "initalign.h"
#include "doendv.h"
#include "initmath.h"
#include "starteqno.h"
#include "setmathchar.h"
#include "mathlimitswitch.h"
#include "mathac.h"
#include "mathradical.h"
#include "lecture.h"
#include "pushnest.h"
#include "noeud.h"
#include "subsup.h"
#include "mathfraction.h"
#include "mathleftright.h"
#include "aftermath.h"
#include "prefixedcommand.h"
#include "issuemessage.h"
#include "openorclosein.h"
#include "impression.h"
#include "shiftcase.h"
#include "doextension.h"

static fontindex maink; //!< index into |font_info|
//static fourquarters mainj; //!<ligature/kern command
//static fourquarters maini; //!<character information bytes for |cur_l|
static LinkedNode *mainp; //!<temporary register for list manipulation

//! the parameter is either |rt_hit| or |false|
static void pack_lig(bool z)
{
	mainp = new LigatureNode(cur_font(), curl, curq->link);
	if (lfthit)
	{
		dynamic_cast<LigatureNode*>(mainp)->subtype = 2;
		lfthit = false;
	}
	if (z && ligstack == nullptr)
	{
		dynamic_cast<LigatureNode*>(mainp)->subtype++;
		rthit = false;
	}
	curq->link = mainp;
	tail = mainp;
	ligaturepresent = false;
}

static void wrapup(bool z)
{
	if (curl < non_char)
	{
		if (curq->link > 0 && dynamic_cast<CharNode*>(tail)->character == cur_font().hyphenchar) 
			insdisc = true; 
		if (ligaturepresent)
			pack_lig(z); 
		if (insdisc)
		{
			insdisc = false;
			if (mode > 0)
				tail_append(new DiscNode); 
		}
	}
}

static void adjust_space_factor(halfword chr)
{
	int mains = sf_code(chr); //main_s: space factor value
	switch (mains < 1000 ? -1 : mains > 1000 ? 1 : 0)
	{
		case 0: // mains == 1000
			space_factor = 1000;
			break;
		case -1: // mains < 1000
			if (mains > 0)
				space_factor = mains;
			break;
		case 1: // mains > 1000
			space_factor = space_factor < 1000 ? 1000 : mains;
	}
}

static void main_loop_lookahead(void)
{
	auto t = getnext();
	if (t.cmd != letter && t.cmd != other_char && t.cmd != char_given)
	{
		t = xtoken(t);
		if (t.cmd != letter && t.cmd != other_char && t.cmd != char_given)
		{
			if (t.cmd == char_num)
				t.chr = scancharnum();
			else
			{
				if (t.cmd == no_boundary)
					bchar = non_char;
				curr = bchar;
				ligstack = nullptr;
				return;
			}
		}
	}
	//main_loop_lookahead_1
	adjust_space_factor(t.chr);
	curr = t.chr;
	ligstack = new LigatureNode(cur_font(), curr, nullptr);
	if (curr == falsebchar)
		curr = non_char;
}

static void main_loop_move_lig(void)
{
	mainp = dynamic_cast<LigatureNode*>(ligstack->lig_ptr);
	if (mainp)
		tail_append(mainp);
	auto temp = ligstack;
	next(ligstack);
	delete temp;
	ligaturepresent = true;
	if (ligstack == nullptr)
		if (mainp)
			main_loop_lookahead();
		else
			curr = bchar;
	else
		curr = ligstack->lig_char.character;
}

[[nodiscard]] static Token append_normal_space(void)
{
	if (space_skip() == zero_glue)
	{
		GlueSpec *Mainp = cur_font().glue;
		if (mainp == nullptr)
		{
			Mainp = new GlueSpec(zero_glue);
			maink = cur_font().parambase+space_code;
			Mainp->width = cur_font().space();
			Mainp->stretch = cur_font().space_stretch();
			Mainp->shrink = cur_font().space_shrink();
			cur_font().glue = Mainp;
		}
		mainp = new GlueNode(Mainp);
		tail_append(mainp);
	}
	else
		tail_append(new GlueNode(space_skip()));
	return getxtoken();
}

static bool main_loop_move_2(halfword chr)
{
	if (cur_font().bc <= chr && chr <= cur_font().ec)
	{
		if (cur_font().char_exists(curl))
		{
			tail_append(ligstack);
			main_loop_lookahead();
			return false;
		}
	}
	charwarning(cur_font(), chr);
	delete ligstack;
	ligstack = 0;
	return true;
}

static bool main_loop_move_1(halfword chr)
{

	if (!ligstack->is_char_node())
		main_loop_move_lig();
	else
		if (main_loop_move_2(chr))
			return true;
	return false;
}

static bool main_loop_move(halfword chr)
{
	if (ligstack == nullptr)
		return true;
	curq = dynamic_cast<CharNode*>(tail);
	curl = ligstack->lig_char.character;
	return main_loop_move_1(chr);
}

static bool main_loop_wrapup(halfword chr)
{
	wrapup(rthit);
	return main_loop_move(chr);
}

[[nodiscard]] static Token main_lig_loop(bool is110, halfword chr)
{
	while (true)
	{
		if (is110)
		{
			if (cur_font().char_tag(curl) != lig_tag || curr == non_char)
			{
				if (main_loop_wrapup(chr))
					return getxtoken();
				continue;
			}
			maink = cur_font().lig_kern_start(cur_font().char_info(curl));
			if (Font::skip_byte(maink) > stop_flag)
				maink = cur_font().lig_kern_restart(Font::infos(maink));
		}
		//main_lig_loop+2
		if (Font::next_char(maink) == curr)
			if (Font::skip_byte(maink) <= stop_flag)
			{
				if (Font::op_byte(maink) >= kern_flag) // c'est un kern
				{
					if (curl < non_char)
					{
						if (curq->link && dynamic_cast<CharNode*>(tail)->character == cur_font().hyphenchar)
							insdisc = true;
						if (ligaturepresent)
						{
							mainp = new LigatureNode(cur_font(), curl, curq->link);
							if (lfthit)
							{
								dynamic_cast<LigatureNode*>(mainp)->subtype = 2;
								lfthit = false;
							}
							if (rthit && ligstack == nullptr)
							{
								dynamic_cast<LigatureNode*>(mainp)->subtype++;
								rthit = false;
							}
							curq->link = mainp;
							tail = mainp;
							ligaturepresent = false;
						}
						if (insdisc)
						{
							insdisc = false;
							if (mode > 0)
								tail_append(new DiscNode);
						}
					}
					tail_append(new KernNode(cur_font().char_kern(Font::infos(maink))));
					if (main_loop_move(chr))
						return getxtoken();
					is110 = true;
					continue;
				}
				// Font::op_byte(maink) < kern_flag => c'est une ligature
				if (curl == non_char)
					lfthit = true;
				else 
					if (ligstack == nullptr)
						rthit = true;
				switch (Font::op_byte(maink))
				{
					// AB -> CB (symboles =:| et =:|>)
					case 1: //a=0 b=0 c=1 => delete current char
					case 5: //a=1 b=0 c=1 => idem
						curl = Font::rem_byte(maink);
						ligaturepresent = true;
						break;
					// AB -> AC (symboles |=: et |=:>)
					case 2: //a=0 b=1 c=0 => delete next char
					case 6: //a=1 b=1 c=0 => delete next char
						curr = Font::rem_byte(maink);
						if (ligstack == nullptr)
						{
							ligstack = new LigatureNode(curr);
							bchar = non_char;
						}
						else 
							if (ligstack->is_char_node())
							{
								mainp = ligstack;
								ligstack = new LigatureNode(curr);
								ligstack->lig_ptr = mainp;
							}
							else
								ligstack->lig_char.character = curr;
						break;
					// AB -> ACB (symbole |=:|)
					case 3: //a=0 b=1 c=1
						curr = Font::rem_byte(maink);
						mainp = ligstack;
						ligstack = new LigatureNode(curr);
						ligstack->link = mainp;
						break;
					// AB -> ACB (symboles |=:|> et |=:|>>)
					case 7: //a=1 b=1 c=1
					case 11://a=2 b=1 c=1
						wrapup(false);
						curq = dynamic_cast<CharNode*>(tail);
						curl = Font::rem_byte(maink);
						ligaturepresent = true;
						break;
					// AB -> C (symbole !=)
					default:
						curl = Font::rem_byte(maink);
						ligaturepresent = true;
						if (ligstack == nullptr)
						{
							if (main_loop_wrapup(chr))
								return getxtoken();
						}
						else
							if (main_loop_move_1(chr))
								return getxtoken();
				}
				if (Font::op_byte(maink) > 4 && Font::op_byte(maink) != 7) // a>=1 et pas a=1,b=1,c=1
				{
					if (main_loop_wrapup(chr))
						return getxtoken();
					is110 = true;
					continue;
				}
				if (curl < non_char)
				{
					is110 = true;
					continue;
				}
				maink = cur_font().bcharlabel;
				is110 = false;
				continue;
			}
		if (Font::skip_byte(maink) == 0)
			maink++;
		else
		{
			if (Font::skip_byte(maink) >= stop_flag)
			{
				if (main_loop_wrapup(chr))
					return getxtoken();
				is110 = true;
				continue;
			}
			maink += Font::skip_byte(maink)+1;
		}
		is110 = false;
	}
}

static void main_loop(Token t)
{
	adjust_space_factor(t.chr);
	bchar = cur_font().bchar;
	falsebchar = cur_font().falsebchar;
	if (mode > 0 && language() != clang)
		fixlanguage();
	curl = t.chr;
	ligstack = new LigatureNode(cur_font(), curl, nullptr);
	curq = dynamic_cast<CharNode*>(tail);
	maink = cancelboundary ? non_address : cur_font().bcharlabel;
	cancelboundary = false;
	if (maink == non_address)
		if (main_loop_move_2(t.chr))
		{
			t = getxtoken();
			curr = curl;
			curl = non_char;
			t = main_lig_loop(false, t.chr);
		}
		else
			t = main_lig_loop(true, t.chr);
}

//! for mode-independent commands
#define ANY_MODE(cmd) vmode+cmd: case hmode+cmd: case mmode+cmd
#define NON_MATH(cmd) vmode+cmd: case hmode+cmd

Token maincontrol(void)
{
	halfword loop = 0;
	if (every_job())
		begintokenlist(every_job(), every_job_text);
	auto t = getxtoken();
	while (true)
	{
		if (tracing_commands() > 0)
			showcurcmdchr(t);
		switch (abs(mode)+t.cmd)
		{
			case hmode+letter:
			case hmode+other_char:
			case hmode+char_given:
				main_loop(t);
				continue;
			case hmode+char_num:
				t.chr = scancharnum();
				main_loop(t);
				continue;
			case hmode+no_boundary:
				t = getxtoken();
				if (t.cmd == letter || t.cmd == other_char || t.cmd == char_given || t.cmd == char_num)
					cancelboundary = true;
				continue;
			case hmode+spacer: 
				if (space_factor == 1000)
				{
					t = append_normal_space();
					continue;
				}
				appspace(mainp, maink);
				break;
			case hmode+ex_space:
			case mmode+ex_space: 
				t = append_normal_space();
				continue;
			case ANY_MODE(relax):
			case vmode+spacer:
			case mmode+spacer:
			case mmode+no_boundary: 
				break;
			case ANY_MODE(ignore_spaces):
				t = getXTokenSkipSpace();
				continue;
			case vmode+stop: 
				if (itsallover(t))
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
				t = insertdollarsign(t);
				break;
			case vmode+hrule:
			case hmode+vrule:
			case mmode+vrule:
				tail_append(scanrulespec(t));
				if (abs(mode) == vmode)
					prev_depth = ignore_depth;
				else 
					if (abs(mode) == hmode)
						space_factor = 1000;
				break;
			case vmode+vskip:
			case hmode+hskip:
			case mmode+hskip:
			case mmode+mskip: 
				appendglue(t.chr);
				break;
			case ANY_MODE(kern):
			case mmode+mkern: 
				appendkern(t.chr);
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
				handlerightbrace(t, loop);
				break;
			case vmode+hmove:
			case hmode+vmove:
			case mmode+vmove:
				scanbox(t.chr == 0 ? scan_normal_dimen() : -scan_normal_dimen());
				break;
			case ANY_MODE(leader_ship):
				scanbox(leader_flag-a_leaders+t.chr);
				break;
			case ANY_MODE(make_box):
				beginbox(0, t);
				break;
			case vmode+start_par: 
				newgraf(t.chr > 0);
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
				newgraf(true);
				break;
			case hmode+start_par:
			case mmode+start_par: 
				indentinhmode(t);
				break;
			case vmode+par_end:
				normalparagraph();
				if (mode > 0)
					buildpage();
				break;
			case hmode+par_end:
				if (alignstate < 0)
					offsave(t);
				endgraf();
				if (mode == vmode)
					buildpage();
				break;
			case hmode+stop:
			case hmode+vskip:
			case hmode+hrule:
			case hmode+un_vbox:
			case hmode+halign: 
				headforvmode(t);
				break;
			case ANY_MODE(insert):
			case hmode+vadjust:
			case mmode+vadjust: 
				begininsertoradjust(t);
				break;
			case ANY_MODE(mark):
				makemark(t);
				break;
			case ANY_MODE(break_penalty):
				appendpenalty();
				break;
			case ANY_MODE(remove_item):
				deletelast(t);
				break;
			case vmode+un_vbox:
			case hmode+un_hbox:
			case mmode+un_hbox: 
				unpackage(t.chr);
				break;
			case hmode+ital_corr: 
				appenditaliccorrection();
				break;
			case mmode+ital_corr:
				tail_append(new KernNode(0));
				break;
			case hmode+discretionary:
			case mmode+discretionary: 
				appenddiscretionary(t.chr);
				break;
			case hmode+accent: 
				makeaccent(t);
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
				initalign(t, loop);
				break;
			case mmode+halign: 
				if (privileged(t))
					if (curgroup == math_shift_group)
						initalign(t, loop);
					else
						offsave(t);
				break;
			case vmode+endv:
			case hmode+endv: 
				doendv(t, loop);
				break;
			case ANY_MODE(end_cs_name):
				error("Extra "+esc("endcsname"), "I'm ignoring this, since I wasn't doing a \\csname.");
				break;
			case hmode+math_shift: 
				initmath();
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
				scanmath(dynamic_cast<Noad*>(tail)->nucleus);
				break;
			case mmode+letter:
			case mmode+other_char:
			case mmode+char_given: 
				setmathchar(math_code(t.chr), t);
				break;
			case mmode+char_num:
				t.chr = scancharnum();
				setmathchar(math_code(t.chr), t);
				break;
			case mmode+math_char_num:
				setmathchar(scanfifteenbitint(), t);
				break;
			case mmode+math_given: 
				setmathchar(t.chr, t);
				break;
			case mmode+delim_num:
				setmathchar(scantwentysevenbitint()>>12, t);
				break;
			case mmode+math_comp:
				tail_append(new Noad);
				tail->type = t.chr;
				scanmath(dynamic_cast<Noad*>(tail)->nucleus);
				break;
			case mmode+limit_switch: 
				mathlimitswitch(t);
				break;
			case mmode+radical: 
				mathradical(t);
				break;
			case mmode+accent:
			case mmode+math_accent: 
				mathac(t.cmd);
				break;
			case mmode+vcenter:
				t = scanspec(vcenter_group);
				normalparagraph();
				pushnest(); 
				mode = -vmode;
				prev_depth = ignore_depth;
				if (every_vbox())
					begintokenlist(every_vbox(), every_vbox_text);
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
				appendchoices();
				break;
			case mmode+sub_mark:
			case mmode+sup_mark: 
				subsup(t.cmd);
				break;
			case mmode+above: 
				mathfraction(t.chr, t);
				break;
			case mmode+left_right: 
				mathleftright(t);
				break;
			case mmode+math_shift: 
				if (curgroup == math_shift_group)
					aftermath();
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
				prefixedcommand(t);
				break;
			case ANY_MODE(after_assignment):
				aftertoken = t = gettoken();
				break;
			case ANY_MODE(after_group):
			{
				t = gettoken();
				auto tk = new TokenNode;
				tk->token = t.tok;
				saveforafter(tk);
				break;
			}
			case ANY_MODE(in_stream):
				openorclosein(t.chr);
				break;
			case ANY_MODE(message):
				issuemessage(t);
				break;
			case ANY_MODE(case_shift):
				shiftcase(t);
				break;
			case ANY_MODE(xray):
				showwhatever(t);
				break;
			case ANY_MODE(extension):
				doextension(t);
		}
		t = getxtoken();
	}
}
