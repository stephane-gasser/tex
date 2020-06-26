#include "impression.h"
#include "texte.h"
#include "xovern.h"
#include <iostream> 
#include <cmath>
#include "scaneightbitint.h" 
#include "gettoken.h"
#include "thetoks.h"
#include "flushlist.h"
#include "error.h"

void print(const std::string &t)
{
	std::string s = t;
	if (txt(s) == 0)
		s = "???";
	else
		if (s.size() == 1)
		{
			if (selector > pseudo)
			{
				printchar(s[0]);
				return;
			}
			unsigned char S = s[0];
			if (S == new_line_char() && selector < pseudo)
			{
				println();
				return;
			}
			int nl = new_line_char();
			new_line_char() = -1;
			for (char c: s)
				printchar(c);
			new_line_char() = nl;
			return;
		}
	for (char c: s)
		printchar(c);
}

void printchar(ASCIIcode s)
{
	if (s == new_line_char())
		if (selector < pseudo)
		{
			println();
			return;
		}
	switch (selector)
	{
		case term_and_log:
			std::cout << xchr[s];
			logfile << xchr[s];
			termoffset++;
			fileoffset++;
			if (termoffset == maxprintline)
			{
				std::cout << "\n";
				termoffset = 0;
			}
			if (fileoffset == maxprintline)
			{
				logfile << "\n";
				fileoffset = 0;
			}
			break;
		case log_only:
			logfile << xchr[s];
			fileoffset++;
			if (fileoffset == maxprintline)
			println();
			break;
		case term_only:
			std::cout << xchr[s];
			termoffset++;
			if (termoffset == maxprintline)
				println();
			break;
		case no_print:
			break;
		case pseudo: 
			if (tally < trickcount)
				trickbuf[tally%errorline] = s;
			break;
		case new_string: 
			if (poolptr < poolsize)
			{
				strpool[poolptr] = s;
				poolptr++;
			}
			break;
		default: 
			writefile[selector] << xchr[s];
	}
	tally++;
}

static void chr_cmd(const std::string &s, halfword chrcode)
{
	print(s);
	printchar(chrcode);
}

void printcmdchr(quarterword cmd, halfword chrcode)
{
	switch (cmd)
	{
		case left_brace:
			chr_cmd("begin-group character ", chrcode);
			break;
		case right_brace:
			chr_cmd("end-group character ", chrcode);
			break;
		case math_shift:
			chr_cmd("math shift character ", chrcode);
			break;
		case mac_param:
			chr_cmd("macro parameter character ", chrcode);
			break;
		case sup_mark:
			chr_cmd("superscript character ", chrcode);
			break;
		case sub_mark:
			chr_cmd("subscript character ", chrcode);
			break;
		case endv: 
			print("end of alignment template");
			break;
		case spacer:
			chr_cmd("blank space ", chrcode);
			break;
		case letter:
			chr_cmd("the letter ", chrcode);
			break;
		case other_char:
			chr_cmd("the character ", chrcode);
			break;
		case assign_glue:
		case assign_mu_glue: 
			if (chrcode < skip_base)
				printskipparam(chrcode-glue_base);
			else 
				if (chrcode < mu_skip_base)
				{
					printesc("skip");
					printint(chrcode-skip_base);
				}
				else
				{
					printesc("muskip");
					printint(chrcode-mu_skip_base);
				}
			break;
		case assign_toks: 
			if (chrcode >= toks_base)
			{
				printesc("toks");
				printint(chrcode-toks_base);
			}
			else
				switch (chrcode)
				{
					case output_routine_loc: 
						printesc("output");
						break;
					case every_par_loc: 
						printesc("everypar");
						break;
					case every_math_loc: 
						printesc("everymath");
						break;
					case every_display_loc: 
						printesc("everydisplay");
						break;
					case every_hbox_loc: 
						printesc("everyhbox");
						break;
					case every_vbox_loc: 
						printesc("everyvbox");
						break;
					case every_job_loc: 
						printesc("everyjob");
						break;
					case every_cr_loc: 
						printesc("everycr");
						break;
					default: 
						printesc("errhelp");
				}
			break;
		case assign_int: 
			if (chrcode < count_base)
				printparam(chrcode-int_base);
			else
			{
				printesc("count");
				printint(chrcode-count_base);
			}
			break;
		case assign_dimen: 
			if (chrcode < scaled_base)
				printlengthparam(chrcode-dimen_base);
			else
			{
				printesc("dimen");
				printint(chrcode-scaled_base);
			}
			break;
		case accent: 
			printesc("accent");
			break;
		case advance: 
			printesc("advance");
			break;
		case after_assignment: 
			printesc("afterassignment");
			break;
		case after_group: 
			printesc("aftergroup");
			break;
		case assign_font_dimen: 
			printesc("fontdimen");
			break;
		case begin_group: 
			printesc("begingroup");
			break;
		case break_penalty: 
			printesc("penalty");
			break;
		case char_num: 
			printesc("char");
			break;
		case cs_name: 
			printesc("csname");
			break;
		case def_font: 
			printesc("font");
			break;
		case delim_num: 
			printesc("delimiter");
			break;
		case divide: 
			printesc("divide");
			break;
		case end_cs_name: 
			printesc("endcsname");
			break;
		case end_group: 
			printesc("endgroup");
			break;
		case ex_space: 
			printesc(" ");
			break;
		case expand_after: 
			printesc("expandafter");
			break;
		case halign: 
			printesc("halign");
			break;
		case hrule: 
			printesc("hrule");
			break;
		case ignore_spaces: 
			printesc("ignorespaces");
			break;
		case insert: 
			printesc("insert");
			break;
		case ital_corr: 
			printesc("/");
			break;
		case mark: 
			printesc("mark");
			break;
		case math_accent: 
			printesc("mathaccent");
			break;
		case math_char_num: 
			printesc("mathchar");
			break;
		case math_choice: 
			printesc("mathchoice");
			break;
		case multiply: 
			printesc("multiply");
			break;
		case no_align: 
			printesc("noalign");
			break;
		case no_boundary: 
			printesc("noboundary");
			break;
		case no_expand: 
			printesc("noexpand");
			break;
		case non_script: 
			printesc("nonscript");
			break;
		case omit: 
			printesc("omit");
			break;
		case radical: 
			printesc("radical");
			break;
		case read_to_cs: 
			printesc("read");
			break;
		case relax: 
			printesc("relax");
			break;
		case set_box: 
			printesc("setbox");
			break;
		case set_prev_graf: 
			printesc("prevgraf");
			break;
		case set_shape: 
			printesc("parshape");
			break;
		case the: 
			printesc("the");
			break;
		case toks_register: 
			printesc("toks");
			break;
		case vadjust: 
			printesc("vadjust");
			break;
		case valign: 
			printesc("valign");
			break;
		case vcenter: 
			printesc("vcenter");
			break;
		case vrule: 
			printesc("vrule");
			break;
		case par_end: 
			printesc("par");
			break;
		case input: 
			if (chrcode == 0)
				printesc("input");
			else
				printesc("endinput");
			break;
		case top_bot_mark: 
			switch (chrcode)
			{
				case first_mark_code: 
					printesc("firstmark");
					break;
				case bot_mark_code: 
					printesc("botmark");
					break;
				case split_first_mark_code: 
					printesc("splitfirstmark");
					break;
				case split_bot_mark_code: 
					printesc("splitbotmark");
					break;
				default: 
					printesc("topmark");
			}
			break;
		case register_: 
			if (chrcode == int_val)
				printesc("count");
			else 
				if (chrcode == dimen_val)
					printesc("dimen");
				else 
					if (chrcode == glue_val)
						printesc("skip");
					else
						printesc("muskip");
			break;
		case set_aux: 
			if (chrcode == vmode)
				printesc("prevdepth");
			else
				printesc("spacefactor");
			break;
		case set_page_int: 
			if (chrcode == 0)
				printesc("deadcycles");
			else
				printesc("insertpenalties");
			break;
		case set_box_dimen: 
			if (chrcode == width_offset)
				printesc("wd");
			else 
				if (chrcode == height_offset)
					printesc("ht");
				else
					printesc("dp");
			break;
		case last_item: 
			switch (chrcode)
			{
				case int_val: 
					printesc("lastpenalty");
					break;
				case dimen_val: 
					printesc("lastkern");
					break;
				case glue_val: 
					printesc("lastskip");
					break;
				case input_line_no_code: 
					printesc("inputlineno");
					break;
				default: 
					printesc("badness");
			}
			break;
		case convert: 
			switch (chrcode)
			{
				case number_code: 
					printesc("number");
					break;
				case roman_numeral_code: 
					printesc("romannumeral");
					break;
				case string_code: 
					printesc("string");
					break;
				case meaning_code: 
					printesc("meaning");
					break;
				case font_name_code: 
					printesc("fontname");
					break;
				default: 
					printesc("jobname");
			}
			break;
		case if_test: 
			switch (chrcode)
			{
				case if_cat_code: 
					printesc("ifcat");
					break;
				case if_int_code: 
					printesc("ifnum");
					break;
				case if_dim_code: 
					printesc("ifdim");
					break;
				case if_odd_code: 
					printesc("ifodd");
					break;
				case if_vmode_code: 
					printesc("ifvmode");
					break;
				case if_hmode_code: 
					printesc("ifhmode");
					break;
				case if_mmode_code: 
					printesc("ifmmode");
					break;
				case if_inner_code: 
					printesc("ifinner");
					break;
				case if_void_code: 
					printesc("ifvoid");
					break;
				case if_hbox_code: 
					printesc("ifhbox");
					break;
				case if_vbox_code: 
					printesc("ifvbox");
					break;
				case ifx_code: 
					printesc("ifx");
					break;
				case if_eof_code: 
					printesc("ifeof");
					break;
				case if_true_code: 
					printesc("iftrue");
					break;
				case if_false_code: 
					printesc("iffalse");
					break;
				case if_case_code: 
					printesc("ifcase");
					break;
			default: 
				printesc("if");
			}
			break;
		case fi_or_else: 
			if (chrcode == fi_code)
				printesc("fi");
			else 
				if (chrcode == or_code)
					printesc("or");
				else
					printesc("else");
			break;
		case tab_mark: 
			if (chrcode == span_code)
				printesc("span");
			else
				chr_cmd("alignment tab character ", chrcode);
			break;
		case car_ret: 
			if (chrcode == cr_code)
				printesc("cr");
			else
				printesc("crcr");
			break;
		case set_page_dimen: 
			switch (chrcode)
			{
				case 0: 
					printesc("pagegoal");
					break;
				case 1: 
					printesc("pagetotal");
					break;
				case 2: 
					printesc("pagestretch");
					break;
				case 3: 
					printesc("pagefilstretch");
					break;
				case 4: 
					printesc("pagefillstretch");
					break;
				case 5: 
					printesc("pagefilllstretch");
					break;
				case 6: 
					printesc("pageshrink");
					break;
				default: 
					printesc("pagedepth");
			}
			break;
		case stop: 
			if (chrcode == 1)
				printesc("dump");
			else
				printesc("end");
			break;
		case hskip: 
			switch (chrcode)
			{
				case skip_code: 
					printesc("hskip");
					break;
				case fil_code: 
					printesc("hfil");
					break;
				case fill_code: 
					printesc("hfill");
					break;
				case ss_code: 
					printesc("hss");
					break;
				default: 
					printesc("hfilneg");
			}
			break;
		case vskip: 
			switch (chrcode)
			{
				case skip_code: 
					printesc("vskip");
					break;
				case fil_code: 
					printesc("vfil");
					break;
				case fill_code: 
					printesc("vfill");
					break;
				case ss_code: 
					printesc("vss");
					break;
				default: 
					printesc("vfilneg");
			}
			break;
		case mskip: 
			printesc("mskip");
			break;
		case kern: 
			printesc("kern");
			break;
		case mkern: 
			printesc("mkern");
			break;
		case hmove: 
			if (chrcode == 1)
				printesc("moveleft");
			else
				printesc("moveright");
			break;
		case vmove: 
			if (chrcode == 1)
				printesc("raise");
			else
				printesc("lower");
			break;
		case make_box: 
			switch (chrcode)
			{
				case box_code: 
					printesc("box");
					break;
				case copy_code: 
					printesc("copy");
					break;
				case last_box_code: 
					printesc("lastbox");
					break;
				case vsplit_code: 
					printesc("vsplit");
					break;
				case vtop_code: 
					printesc("vtop");
					break;
				case vtop_code+vmode: 
					printesc("vbox");
					break;
				default: 
					printesc("hbox");
			}
			break;
		case leader_ship: 
			if (chrcode == a_leaders)
				printesc("leaders");
			else 
				if (chrcode == c_leaders)
					printesc("cleaders");
				else 
					if (chrcode == x_leaders)
						printesc("xleaders");
					else
						printesc("shipout");
			break;
		case start_par: 
			if (chrcode == 0)
				printesc("noindent");
			else
				printesc("indent");
			break;
		case remove_item: 
			if (chrcode == glue_node)
				printesc("unskip");
				else 
					if (chrcode == kern_node)
						printesc("unkern");
					else
						printesc("unpenalty");
			break;
		case un_hbox: 
			if (chrcode == copy_code)
				printesc("unhcopy");
			else
				printesc("unhbox");
			break;
		case un_vbox: 
			if (chrcode == copy_code)
				printesc("unvcopy");
			else
			printesc("unvbox");
			break;
		case discretionary: 
			if (chrcode == 1)
				printesc("-");
			else
				printesc("discretionary");
			break;
		case eq_no: 
			if (chrcode == 1)
				printesc("leqno");
			else
				printesc("eqno");
			break;
		case math_comp: 
			switch (chrcode)
			{
				case ord_noad: 
					printesc("mathord");
					break;
				case op_noad: 
					printesc("mathop");
					break;
				case bin_noad: 
					printesc("mathbin");
					break;
				case rel_noad: 
					printesc("mathrel");
					break;
				case open_noad: 
					printesc("mathopen");
					break;
				case close_noad: 
					printesc("mathclose");
					break;
				case punct_noad: 
					printesc("mathpunct");
					break;
				case inner_noad: 
					printesc("mathinner");
					break;
				case under_noad: 
					printesc("underline");
					break;
				default: 
					printesc("overline");
			}
			break;
		case limit_switch: 
			if (chrcode == limits)
			printesc("limits");
			else 
				if (chrcode == no_limits)
					printesc("nolimits");
				else
				printesc("displaylimits");
			break;
		case math_style: 
			printstyle(chrcode);
			break;
		case above: 
			switch (chrcode)
			{
				case over_code: 
					printesc("over");
					break;
				case atop_code: 
					printesc("atop");
					break;
				case delimited_code+above_code: 
					printesc("abovewithdelims");
					break;
				case delimited_code+over_code: 
					printesc("overwithdelims");
					break;
				case delimited_code+atop_code: 
					printesc("atopwithdelims");
					break;
				default: 
					printesc("above");
			}
			break;
		case left_right: 
			if (chrcode == left_noad)
				printesc("left");
			else
				printesc("right");
			break;
		case prefix: 
			if (chrcode == 1)
				printesc("long");
			else 
				if (chrcode == 2)
					printesc("outer");
				else
					printesc("global");
		case def: 
			if (chrcode == 0)
				printesc("def");
			else 
				if (chrcode == 1)
					printesc("gdef");
				else 
					if (chrcode == 2)
						printesc("edef");
					else
						printesc("xdef");
			break;
		case let: 
			if (chrcode != normal)
				printesc("futurelet");
			else
				printesc("let");
			break;
		case shorthand_def: 
			switch (chrcode)
			{
				case char_def_code: 
					printesc("chardef");
					break;
				case math_char_def_code: 
					printesc("mathchardef");
					break;
				case count_def_code: 
					printesc("countdef");
					break;
				case dimen_def_code: 
					printesc("dimendef");
					break;
				case skip_def_code: 
					printesc("skipdef");
					break;
				case mu_skip_def_code: 
					printesc("muskipdef");
					break;
				default: printesc("toksdef");
			}
			break;
		case char_given:
			printesc("char");
			printhex(chrcode);
			break;
		case math_given:
			printesc("mathchar");
			printhex(chrcode);
			break;
		case def_code: 
			if (chrcode == cat_code_base)
				printesc("catcode");
			else 
				if (chrcode == math_code_base)
					printesc("mathcode");
				else 
					if (chrcode == lc_code_base)
						printesc("lccode");
					else 
						if (chrcode == uc_code_base)
							printesc("uccode");
						else 
							if (chrcode == sf_code_base)
								printesc("sfcode");
							else
								printesc("delcode");
			break;
		case def_family: 
			printsize(chrcode-math_font_base);
			break;
		case hyph_data: 
			if (chrcode == 1)
				printesc("patterns");
			else
				printesc("hyphenation");
			break;
		case assign_font_int: 
			if (chrcode == 0)
				printesc("hyphenchar");
			else
				printesc("skewchar");
			break;
		case set_font:
			print("select font ");
			slowprint(fontname[chrcode]);
			if (fontsize[chrcode] != fontdsize[chrcode])
			{
				print(" at ");
				printscaled(fontsize[chrcode]);
				print("pt");
			}
			break;
		case set_interaction: 
			switch (chrcode)
			{
				case batch_mode: 
					printesc("batchmode");
					break;
				case nonstop_mode: 
					printesc("nonstopmode");
					break;
				case scroll_mode: 
					printesc("scrollmode");
					break;
				default: 
					printesc("errorstopmode");
			}
			break;
		case in_stream: 
			if (chrcode == 0)
				printesc("closein");
			else
				printesc("openin");
			break;
		case message: 
			if (chrcode == 0)
				printesc("message");
			else
				printesc("errmessage");
			break;
		case case_shift: 
			if (chrcode == lc_code_base)
				printesc("lowercase");
			else
				printesc("uppercase");
			break;
		case xray: 
			switch (chrcode)
			{
				case show_box_code: 
					printesc("showbox");
					break;
				case show_the_code: 
					printesc("showthe");
					break;
				case show_lists: 
					printesc("showlists");
					break;
				default: 
					printesc("show");
			}
			break;
		case undefined_cs: 
			print("undefined");
			break;
		case call: 
			print("macro");
			break;
		case long_call: 
			printesc("long macro");
			break;
		case outer_call: 
			printesc("outer macro");
			break;
		case long_outer_call:
			printesc("long");
			printesc("outer macro");
			break;
		case end_template: 
			printesc("outer endtemplate");
			break;
		case extension: 
			switch (chrcode)
			{
				case open_node: 
					printesc("openout");
					break;
				case write_node: 
					printesc("write");
					break;
				case close_node: 
					printesc("closeout");
					break;
				case special_node: 
					printesc("special");
					break;
				case immediate_code: 
					printesc("immediate");
					break;
				case set_language_code: 
					printesc("setlanguage");
					break;
				default: 
					print("[unknown extension!]");
			}
			break;
		default: 
			print("[unknown command code!]");
	}
}

void printcs(int p)
{
	if (p < hash_base)
		if (p >= single_base)
			if (p == null_cs)
			{
				printesc("csname");
				printesc("endcsname");
				printchar(' ');
			}
			else
			{
				printesc(std::string(1, char(p-single_base)));
				if (cat_code(p-single_base) == letter)
					printchar(' ');
			}
		else 
			if (p < active_base)
				printesc("IMPOSSIBLE.");
			else
				printchar(p-active_base);
	else 
		if (p >= undefined_control_sequence)
			printesc("IMPOSSIBLE.");
		else 
			if (text(p) < 0 || text(p) >= strptr)
				printesc("NONEXISTENT.");
			else
			{
				printesc(TXT(hash[p].rh));
				printchar(' ');
			}
}

void printcurrentstring(void)
{
	for (auto j = strstart[strptr]; j < poolptr; j++)
		printchar(strpool[j]);
}

void printdelimiter(halfword p)
{
	int a = (mem[p].qqqq.b0<<8)+mem[p].qqqq.b1;
	a = (a<<12)+(mem[p].qqqq.b2<<8)+mem[p].qqqq.b3;
	if (a < 0)
		printint(a);
	else
		printhex(a);
}

std::string esc(const std::string &s) 
{
	return "\\"+s;
}

void printesc(const std::string &s)
{
	auto &c = escape_char();
	if (c >= 0 && c < 256)
		printchar(c);
	slowprint(txt(s));
}

void printfamandchar(halfword p)
{
	printesc("fam");
	printint(type(p));
	printchar(' ');
	print(TXT(subtype(p)));
}

void printfilename(const std::string &n, const std::string &a, const std::string &e)
{
	slowprint(a);
	slowprint(n);
	slowprint(e);
}

void printfontandchar(int p)
{
	if (p > memend)
		printesc("CLOBBERED.");
	else
	{
		if (type(p) < 0 || type(p) > fontmax)
		printchar('*');
		else
		printesc(TXT(text(frozen_null_font+type(p))));
		printesc("FONT");
		printchar(' ');
		print(TXT(subtype(p)));
	}
}

void printglue(scaled d, int order, const std::string &s)
{
	printscaled(d);
	if (order < 0 || order > 3)
		print("foul");
	else 
		if (order > 0)
		{
			print("fil");
			for (;order > 1; order--)
				printchar('l');
		}
		else 
			if (txt(s))
				print(s);
}

void printhex(int n)
{
	int k = 0;
	printchar('"');
	do
	{
		dig[k] = n%16;
		n /= 16;
		k++;
	}
	while (n);
	printthedigs(k);
}

void printint(int n)
{
	int k = 0;
	if (n < 0) // nombre négatif
	{
		printchar('-');
		if (n > -100000000) // taille raisonnable
			n = -n;
		else // nombre super négatif => probablement une manip de vieux briscard en 32 bits [inutile]
		{
			int m = -1-n;
			n = m/10; // (-1-n)/10
			m = m%10+1; // (-1-n)%10+1
			k = 1;
			if (m < 10)
				dig[0] = m;
			else
			{
				dig[0] = 0;
				n++;
			}
		}
	}
	do
	{
		dig[k] = n%10;
		n /= 10;
		k++;
	} while (n);
	printthedigs(k);
}

void printlengthparam(int n)
{
	switch (n)
	{
		case par_indent_code:
			printesc("parindent");
			break;
		case math_surround_code:
			printesc("mathsurround");
			break;
		case line_skip_limit_code:
			printesc("lineskiplimit");
			break;
		case hsize_code:
			printesc("hsize");
			break;
		case vsize_code:
			printesc("vsize");
			break;
		case max_depth_code:
			printesc("maxdepth");
			break;
		case split_max_depth_code:
			printesc("splitmaxdepth");
			break;
		case box_max_depth_code:
			printesc("boxmaxdepth");
			break;
		case hfuzz_code:
			printesc("hfuzz");
			break;
		case vfuzz_code:
			printesc("vfuzz");
			break;
		case delimiter_shortfall_code:
			printesc("delimitershortfall");
			break;
		case null_delimiter_space_code:
			printesc("nulldelimiterspace");
			break;
		case script_space_code:
			printesc("scriptspace");
			break;
		case pre_display_size_code:
			printesc("predisplaysize");
			break;
		case display_width_code:
			printesc("displaywidth");
			break;
		case display_indent_code:
			printesc("displayindent");
			break;
		case overfull_rule_code:
			printesc("overfullrule");
			break;
		case hang_indent_code:
			printesc("hangindent");
			break;
		case h_offset_code:
			printesc("hoffset");
			break;
		case v_offset_code:
			printesc("voffset");
			break;
		case emergency_stretch_code:
			printesc("emergencystretch");
			break;
		default:
			print("[unknown dimen parameter!]");
	}
}

void println(void)
{
	switch (selector)
	{
		case term_and_log:
			std::cout << "\n";
			logfile << "\n";
			termoffset = 0;
			fileoffset = 0;
			break;
		case log_only:
			logfile << "\n";
			fileoffset = 0;
			break;
		case term_only:
			std::cout << "\n";
			termoffset = 0;
			break;
		case no_print:
		case pseudo:
		case new_string: 
			break;
		default: 
			writefile[selector] << "\n";
	}
}

void printmark(int p)
{
	printchar('{');
	if (p < himemmin || p > memend)
		printesc("CLOBBERED.");
	else
		showtokenlist(link(p), 0, maxprintline-10);
	printchar('}');
}

void printmeaning(void)
{
	printcmdchr(curcmd, curchr);
	if (curcmd >= call)
	{
		printchar(':');
		println();
		tokenshow(curchr);
	}
	else 
		if (curcmd == top_bot_mark)
		{
			printchar(':');
			println();
			tokenshow(curmark[curchr]);
		}
}

void printmode(int m)
{
	if (m > 0)
	switch (m/101)
	{
		case 0: 
			print("vertical");
			break;
		case 1: 
			print("horizontal");
			break;
		case 2: 
			print("display math");
	}
	else 
		if (m == 0)
			print("no");
		else
			switch ((-m)/101)
			{
				case 0: 
					print("internal vertical");
					break;
				case 1: 
					print("restricted horizontal");
					break;
				case 2: 
				print("math");
			}
	print(" mode");
}

void printnl(const std::string &s)
{
	if ((termoffset > 0 && selector%2 == 1) || (fileoffset > 0 && selector >= log_only))
		println();
	print(s);
}

void printparam(int n)
{
	switch (n)
	{
		case pretolerance_code:
			printesc("pretolerance");
			break;
		case tolerance_code:
			printesc("tolerance");
			break;
		case line_penalty_code:
			printesc("linepenalty");
			break;
		case hyphen_penalty_code:
			printesc("hyphenpenalty");
			break;
		case ex_hyphen_penalty_code:
			printesc("exhyphenpenalty");
			break;
		case club_penalty_code:
			printesc("clubpenalty");
			break;
		case widow_penalty_code:
			printesc("widowpenalty");
			break;
		case display_widow_penalty_code:
			printesc("displaywidowpenalty");
			break;
		case broken_penalty_code:
			printesc("brokenpenalty");
			break;
		case bin_op_penalty_code:
			printesc("binoppenalty");
			break;
		case rel_penalty_code:
			printesc("relpenalty");
			break;
		case pre_display_penalty_code:
			printesc("predisplaypenalty");
			break;
		case post_display_penalty_code:
			printesc("postdisplaypenalty");
			break;
		case inter_line_penalty_code:
			printesc("interlinepenalty");
			break;
		case double_hyphen_demerits_code:
			printesc("doublehyphendemerits");
			break;
		case final_hyphen_demerits_code:
			printesc("finalhyphendemerits");
			break;
		case adj_demerits_code:
			printesc("adjdemerits");
			break;
		case mag_code:
			printesc("mag");
			break;
		case delimiter_factor_code:
			printesc("delimiterfactor");
			break;
		case looseness_code:
			printesc("looseness");
			break;
		case time_code:
			printesc("time");
			break;
		case day_code:
			printesc("day");
			break;
		case month_code:
			printesc("month");
			break;
		case year_code:
			printesc("year");
			break;
		case show_box_breadth_code:
			printesc("showboxbreadth");
			break;
		case show_box_depth_code:
			printesc("showboxdepth");
			break;
		case hbadness_code:
			printesc("hbadness");
			break;
		case vbadness_code:
			printesc("vbadness");
			break;
		case pausing_code:
			printesc("pausing");
			break;
		case tracing_online_code:
			printesc("tracingonline");
			break;
		case tracing_macros_code:
			printesc("tracingmacros");
			break;
		case tracing_stats_code:
			printesc("tracingstats");
			break;
		case tracing_paragraphs_code:
			printesc("tracingparagraphs");
			break;
		case tracing_pages_code:
			printesc("tracingpages");
			break;
		case tracing_output_code:
			printesc("tracingoutput");
			break;
		case tracing_lost_chars_code:
			printesc("tracinglostchars");
			break;
		case tracing_commands_code:
			printesc("tracingcommands");
			break;
		case tracing_restores_code:
			printesc("tracingrestores");
			break;
		case uc_hyph_code:
			printesc("uchyph");
			break;
		case output_penalty_code:
			printesc("outputpenalty");
			break;
		case max_dead_cycles_code:
			printesc("maxdeadcycles");
			break;
		case hang_after_code:
			printesc("hangafter");
			break;
		case floating_penalty_code:
			printesc("floatingpenalty");
			break;
		case global_defs_code:
			printesc("globaldefs");
			break;
		case cur_fam_code:
			printesc("fam");
			break;
		case escape_char_code:
			printesc("escapechar");
			break;
		case default_hyphen_char_code:
			printesc("defaulthyphenchar");
			break;
		case default_skew_char_code:
			printesc("defaultskewchar");
			break;
		case end_line_char_code:
			printesc("endlinechar");
			break;
		case new_line_char_code:
			printesc("newlinechar");
			break;
		case language_code:
			printesc("language");
			break;
		case left_hyphen_min_code:
			printesc("lefthyphenmin");
			break;
		case right_hyphen_min_code:
			printesc("righthyphenmin");
			break;
		case holding_inserts_code:
			printesc("holdinginserts");
			break;
		case error_context_lines_code:
			printesc("errorcontextlines");
			break;
		default:
			print("[unknown integer parameter!]");
	}
}

void printromanint(int n)
{
	constexpr char s[] = "m2d5c2l5x2v5i";
	int j = 0;
	int v = 1000;
	while (true)
	{
		while (n >= v)
		{
			printchar(s[j]);
			n -= v;
		}
		if (n <= 0)
			return;
		int k = j+2;
		int u = v/(s[j+1]-'0');
		if (s[j+1] == '2')
		{
			k += 2;
			u /= s[j+3]-'0';
		}
		if (n+u >= v)
		{
			printchar(s[k]);
			n += u;
		}
		else
		{
			j += 2;
			v /= s[j-1]-'0';
		}
	}
}

void printruledimen(scaled d)
{
	if (is_running(d))
		printchar('*');
	else
		printscaled(d);
}

void printscaled(scaled s)
{
	if (s < 0)
	{
		printchar('-');
		s = -s;
	}
	printint(s/unity);
	printchar('.');
	s = 10*(s%unity)+5;
	scaled delta = 10;
	do
	{
		if (delta > unity)
		s += 0x80'00-50000;
		printchar('0'+s/unity);
		s = 10*(s%unity);
		delta *= 10;
	} while (s > delta);
}

void printsize(int s)
{
	if (s == 0)
		printesc("textfont");
	else 
		if (s == 16)
			printesc("scriptfont");
		else
			printesc("scriptscriptfont");
}

void printskipparam(int n)
{
	switch (n)
	{
		case line_skip_code: 
			printesc("lineskip");
			break;
		case baseline_skip_code: 
			printesc("baselineskip");
			break;
		case par_skip_code: 
			printesc("parskip");
			break;
		case above_display_skip_code: 
			printesc("abovedisplayskip");
			break;
		case below_display_skip_code: 
			printesc("belowdisplayskip");
			break;
		case above_display_short_skip_code: 
			printesc("abovedisplayshortskip");
			break;
		case below_display_short_skip_code: 
			printesc("belowdisplayshortskip");
			break;
		case left_skip_code: 
			printesc("leftskip");
			break;
		case right_skip_code: 
			printesc("rightskip");
			break;
		case top_skip_code: 
			printesc("topskip");
			break;
		case split_top_skip_code: 
			printesc("splittopskip");
			break;
		case tab_skip_code: 
			printesc("tabskip");
			break;
		case space_skip_code: 
			printesc("spaceskip");
			break;
		case xspace_skip_code: 
			printesc("xspaceskip");
			break;
		case par_fill_skip_code: 
			printesc("parfillskip");
			break;
		case thin_mu_skip_code: 
			printesc("thinmuskip");
			break;
		case med_mu_skip_code: 
			printesc("medmuskip");
			break;
		case thick_mu_skip_code: 
			printesc("thickmuskip");
			break;
		default: 
			print("[unknown glue parameter!]");
	}
}

void printspec(int p, const std::string &s)
{
	if (p < memmin || p >= lomemmax)
		printchar('*');
	else
	{
		printscaled(width(p));
		if (txt(s))
			print(s);
		if (stretch(p))
		{
			print(" plus ");
			printglue(stretch(p), type(p), s);
		}
		if (shrink(p))
		{
			print(" minus ");
			printglue(shrink(p), subtype(p), s);
		}
	}
}

void printstyle(int c)
{
	switch (c/2)
	{
		case 0: 
			printesc("displaystyle");
			break;
		case 1: 
			printesc("textstyle");
			break;
		case 2: 
			printesc("scriptstyle");
			break;
		case 3:
			printesc("scriptscriptstyle");
			break;
		default:
			print("Unknown style!");
	}
}

void printsubsidiarydata(halfword p, ASCIIcode c)
{
	if (cur_length() >= depththreshold)
	{
		if (link(p))
			print(" []");
	}
	else
	{
		append_char(c);
		tempptr = p;
		switch (link(p))
		{
			case 1:
				println();
				printcurrentstring();
				printfamandchar(p);
				break;
			case 2: 
				showinfo();
				break;
			case 3: 
				if (info(p) == 0)
				{
					println();
					printcurrentstring();
					print("{}");
				}
				else
					showinfo();
		}
		poolptr--;
	}
}

void printthedigs(eightbits k)
{
	while (k > 0)
	{
		k--;
		if (dig[k] < 10)
			printchar('0'+dig[k]);
		else
			printchar('A'+dig[k]-10);
	}
}

static void print_plus(int i, const std::string &s)
{
	if (pagesofar[i])
	{
		print(" plus ");
		printscaled(pagesofar[i]);
		print(s);
	}
}

void printtotals(void)
{
	printscaled(page_total);
	print_plus(2, "");
	print_plus(3, "fil");
	print_plus(4, "fill");
	print_plus(5, "filll");
	if (page_shrink)
	{
		print(" minus ");
		printscaled(page_shrink);
	}
}

void printtwo(int n)
{
	n = abs(n)%100;
	printchar('0'+n/10);
	printchar('0'+n%10);
}

void printwritewhatsit(const std::string &s, halfword p)
{
	printesc(s);
	if (write_stream(p) < 16)
		printint(write_stream(p));
	else 
		if (write_stream(p) == 16)
			printchar('*');
		else
			printchar('-');
}

void slowprint(int s)
{
	if (s >= strptr || s < 256)
		printchar(s);
	else
		for (int j = strstart[s]; j < strstart[s+1]; j++)
			printchar(strpool[j]);
}

void slowprint(const std::string &s)
{
	for (auto c: s)
		printchar(c);
}

void sprintcs(halfword p)
{
	if (p < hash_base)
		if (p < single_base)
			printchar(p-active_base);
		else 
			if (p < null_cs)
				printesc(std::string(1, char(p-single_base)));
			else
			{
				printesc("csname");
				printesc("endcsname");
			}
	else
		printesc(TXT(text(p)));
}

void print_err(const std::string &s)
{
	printnl("! ");
	print(s);
}

void showtokenlist(int p, int  q, int l)
{
	ASCIIcode matchchr = '#';
	ASCIIcode n = '0';
	tally = 0;
	while (p && tally < l)
	{
		if (p == q)
		{
			firstcount = tally;
			trickcount = tally+1+errorline-halferrorline;
			if (trickcount < errorline)
				trickcount = errorline;
		}
		if (p < himemmin || p > memend)
		{
			printesc("CLOBBERED.");
			return;
		}
		if (info(p) >= cs_token_flag)
			printcs(info(p)-cs_token_flag);
		else
		{
			int m = info(p)/0x1'00;
			int c = info(p)%0x1'00;
			if (info(p) < 0)
				printesc("BAD.");
			else
				switch (m)
				{
					case left_brace:
					case right_brace:
					case math_shift:
					case tab_mark:
					case sup_mark:
					case sub_mark:
					case spacer:
					case letter:
					case other_char: 
						printchar(c);
						break;
					case mac_param:
						printchar(c);
						printchar(c);
						break;
					case out_param:
						printchar(matchchr);
						if (c <= 9)
							printchar(c+'0');
						else
						{
							printchar('!');
							return;
						}
						break;
					case match:
						matchchr = c;
						printchar(c);
						n++;
						printchar(n);
						if (n > '9')
							return;
						break;
					case end_match: 
						print("->");
						break;
					default:
			  			printesc("BAD.");
				}
		}
		p = link(p);
	}
	if (p)
		printesc("ETC.");
}

void tokenshow(halfword p)
{
	if (p)
		showtokenlist(link(p), 0, 10000000);
}

//! a frozen font identifier's name
static halfword& font_id_text(halfword p) { return text(font_id_base+p); }

void shortdisplay(int p)
{
	while (p > memmin)
	{
		if (p >= himemmin)
		{
			if (p <= memend)
			{
				if (font(p) != fontinshortdisplay)
				{
					if (font(p) < 0 || font(p) > fontmax)
						printchar('*');
					else
						printesc(TXT(font_id_text(p)));
					printchar(' ');
					fontinshortdisplay = font(p);
				}
				printchar(character(p));
			}
		}
		else
		switch (type(p))
		{
			case hlist_node:
			case vlist_node:
			case ins_node:
			case whatsit_node:
			case mark_node:
			case adjust_node:
			case unset_node: 
				print("[]");
				break;
			case rule_node: 
				printchar('|');
				break;
			case glue_node: 
				if (glue_ptr(p) != zero_glue)
					printchar(' ');
				break;
			case math_node:
				printchar('$');
				break;
			case ligature_node:
				shortdisplay(lig_ptr(p));
				break;
			case disc_node:
				shortdisplay(pre_break(p));
				shortdisplay(post_break(p));
				for (int n = replace_count(p); n > 0; n--)
					if (link(p))
						p = link(p);
		}
		p = link(p);
	}
}

static void node_list_display(int p)
{
	append_char('.'); 
	shownodelist(p); 
	flush_char(); 
}

void shownodelist(int p)
{
	if (cur_length() > depththreshold)
	{
		if (p > 0)
			print(" []");
		return;
	}
	int n = 0;
	while (p > memmin)
	{
		println();
		printcurrentstring();
		if (p > memend)
		{
			print("Bad link, display aborted.");
			return;
		}
		n++;
		if (n > breadthmax)
		{
			print("etc.");
			return;
		}
		if (p >= himemmin)
			printfontandchar(p);
		else
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
					if (type(p) == hlist_node)
						printesc("h");
					else 
						if (type(p) == vlist_node)
							printesc("v");
						else
							printesc("unset");
					print("box(");
					printscaled(height(p));
					printchar('+');
					printscaled(depth(p));
					print(")x");
					printscaled(width(p));
					if (type(p) == unset_node)
					{
						if (span_count(p))
						{
							print(" (");
							printint(span_count(p)+1);
							print(" columns)");
						}
						if (glue_stretch(p))
						{
							print(", stretch ");
							printglue(glue_stretch(p), glue_order(p), 0);
						}
						if (glue_shrink(p))
						{
							print(", shrink ");
							printglue(glue_shrink(p), glue_sign(p), 0);
						}
					}
					else
					{
						g = glue_set(p);
						if (g && glue_sign(p))
						{
							print(", glue set ");
							if (glue_sign(p) == shrinking)
								print("- ");
							if (!std::isfinite(glue_set(p)))
								print("?.?");
							else 
								if (abs(g) > 20000.0)
								{
									if (g > 0.0)
										printchar('>');
									else
										print("< -");
									printglue(20000*unity, glue_order(p), 0);
								}
								else
									printglue(round(unity*g), glue_order(p), 0);
						}
						if (shift_amount(p))
						{
							print(", shifted ");
							printscaled(shift_amount(p));
						}
					}
					node_list_display(list_ptr(p));
					break;
				case rule_node:
					printesc("rule(");
					printruledimen(width(p));
					printchar('+');
					printruledimen(depth(p));
					print(")x");
					printruledimen(width(p));
					break;
				case ins_node:
					printesc("insert");
					printint(subtype(p));
					print(", natural size ");
					printscaled(height(p));
					print("; split(");
					printspec(split_top_ptr(p), 0);
					printchar(',');
					printscaled(depth(p));
					print("); float cost ");
					printint(float_cost(p));
					node_list_display(ins_ptr(p));
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case 0:
							printwritewhatsit("openout", p);
							printchar('=');
							printfilename(TXT(open_name(p)), TXT(open_area(p)), TXT(open_ext(p)));
							break;
						case 1:
							printwritewhatsit("write", p);
							printmark(link(p+1));
							break;
						case 2: 
							printwritewhatsit("closeout", p); 
							break;
						case 3:
							printesc("special");
							printmark(link(p+1));
							break;
						case 4:
							printesc("setlanguage");
							printint(link(p+1));
							print(" (hyphenmin"); 
							printint(type(p+1));
							printchar(',');
							printint(subtype(p+1));
							printchar(')');
							break;
						default: 
							print("whatsit?");
					}
					break;
				case glue_node:
					if (subtype(p) >= 100)
					{
						printesc("");
						if (subtype(p) == 101)
							printchar('c');
						else 
							if (subtype(p) == 102)
								printchar('x');
						print("leaders ");
						printspec(glue_ptr(p), 0);
						node_list_display(leader_ptr(p));
					}
					else
					{
						printesc("glue");
						if (subtype(p))
						{
							printchar('(');
							if (subtype(p) < 98)
								printskipparam(subtype(p)-1);
							else 
								if (subtype(p) == 98)
								printesc("nonscript");
							else
								printesc("mskip");
							printchar(')');
						}
						if (subtype(p) != 98)
						{
							printchar(' ');
							if (subtype(p) < 98)
								printspec(info(p+1), 0);
							else
								printspec(info(p+1), "mu");
						}
					}
				case kern_node:
					if (subtype(p) != mu_glue)
					{
						printesc("kern");
						if (subtype(p) != normal)
							printchar(' ');
						printscaled(width(p));
						if (subtype(p) == acc_kern)
							print(" (for accent)");
					}
					else
					{
						printesc("mkern");
						printscaled(width(p));
						print("mu");
					}
					break;
				case math_node:
					printesc("math");
					if (subtype(p) == before)
						print("on");
					else
						print("off");
					if (width(p))
					{
						print(", surrounded ");
						printscaled(width(p));
					}
					break;
				case ligature_node:
					printfontandchar(p+1);
					print(" (ligature ");
					if (subtype(p) > 1)
						printchar('|');
					fontinshortdisplay = type(p+1);
					shortdisplay(link(p+1));
					if (subtype(p)%2)
						printchar('|');
					printchar(')');
					break;
				case penalty_node:
					printesc("penalty ");
					printint(penalty(p));
					break;
				case disc_node:
					printesc("discretionary");
					if (subtype(p) > 0)
					{
						print(" replacing ");
						printint(subtype(p));
					}
					node_list_display(pre_break(p));
					append_char('|');
					shownodelist(post_break(p));
					flush_char();
					break;
				case mark_node:
					printesc("mark");
					printmark(mark_ptr(p));
					break;
				case adjust_node:
					printesc("vadjust");
					node_list_display(adjust_ptr(p));
					break;
				case style_node: 
					printstyle(subtype(p));
					break;
				case choice_node:
					printesc("mathchoice");
					append_char('D');
					shownodelist(info(p+1));
					flush_char();
					append_char('T');
					shownodelist(link(p+1));
					flush_char();
					append_char('S');
					shownodelist(info(p+2));
					flush_char();
					append_char('s');
					shownodelist(link(p+2));
					flush_char();
					break;
				case ord_noad:
				case op_noad:
				case bin_noad:
				case rel_noad:
				case open_noad:
				case close_noad:
				case punct_noad:
				case inner_noad:
				case radical_noad:
				case over_noad:
				case under_noad:
				case vcenter_noad:
				case accent_noad:
				case left_noad:
				case right_noad:
					switch (type(p))
					{
						case ord_noad: 
							printesc("mathord");
							break;
						case op_noad: 
							printesc("mathop");
							break;
						case bin_noad: 
							printesc("mathbin");
							break;
						case rel_noad: 
							printesc("mathrel");
							break;
						case open_noad: 
							printesc("mathopen");
							break;
						case close_noad: 
							printesc("mathclose");
							break;
						case punct_noad: 
							printesc("mathpunct");
							break;
						case inner_noad: 
							printesc("mathinner");
							break;
						case over_noad: 
							printesc("overline");
							break;
						case under_noad: 
							printesc("underline");
							break;
						case vcenter_noad: 
							printesc("vcenter");
							break;
						case radical_noad:
							printesc("radical");
							printdelimiter(left_delimiter(4));
							break;
						case accent_noad:
							printesc("accent");
							printfamandchar(accent_chr(p));
							break;
						case left_noad:
							printesc("left");
							printdelimiter(delimiter(p));
							break;
						case right_noad:
							printesc("right");
							printdelimiter(delimiter(p));
					}
					if (subtype(p))
						if (subtype(p) == limits)
							printesc("limits");
						else
							printesc("nolimits");
					if (type(p) < left_noad)
						printsubsidiarydata(nucleus(p), '.');
					printsubsidiarydata(supscr(p), '^');
					printsubsidiarydata(subscr(p), '_');
					break;
				case fraction_noad:
					printesc("fraction, thickness ");
					if (new_hlist(p) == default_code)
						print("= default");
					else
						printscaled(new_hlist(p));
					if (small_fam(left_delimiter(p))
					 || small_char(left_delimiter(p))
					 || large_fam(left_delimiter(p))
					 || large_char(left_delimiter(p)))
					{
						print(", left-delimiter ");
						printdelimiter(left_delimiter(p));
					}
					if (small_fam(right_delimiter(p))
					 || small_char(right_delimiter(p))
					 || large_fam(right_delimiter(p))
					 || large_char(right_delimiter(p)))
					{
						print(", right-delimiter ");
						printdelimiter(right_delimiter(p));
					}
					printsubsidiarydata(numerator(p), '\\');
					printsubsidiarydata(denominator(p), '/');
					break;
				default: 
					print("Unknown node type!");
			}
		p = link(p);
	}
}

void showinfo(void)
{
	 shownodelist(info(tempptr));
}

static int show_box_breadth(void) { return int_par(show_box_breadth_code); }
static int show_box_depth(void) { return int_par(show_box_depth_code); }

void showbox(halfword p)
{  
	depththreshold = show_box_depth();
	breadthmax = show_box_breadth();
	if (breadthmax <= 0)
		breadthmax = 5;
	if (poolptr+depththreshold >= poolsize)
		depththreshold = poolsize-poolptr-1;
	shownodelist(p);
	println();
}

static void begin_pseudoprint(int l)
{
	l = tally;
	tally = 0;
	selector = pseudo;
	trickcount = 1000000;
}

static void set_trick_count(void)
{
	firstcount = tally; 
	trickcount = tally+1+errorline-halferrorline;
	if (trickcount < errorline)
		trickcount = errorline;
}

static int error_context_lines(void) { return int_par(error_context_lines_code); }

void showcontext(void)
{
	int l;
	baseptr = inputptr;
	inputstack[baseptr] = curinput; 
	int nn = -1;
	bool bottomline = false;
	while (true) 
	{
		curinput = inputstack[baseptr];
		if (state)
			if (txt(name) > 17 || baseptr == 0)
				bottomline = true;
		if (baseptr == inputptr || bottomline || nn < error_context_lines())
		{
			if (baseptr == inputptr || state != token_list || token_type != backed_up || loc)
			{
				tally = 0;
				oldsetting = selector;
				if (state)
				{
					if (txt(name) <= 17)
						if (terminal_input(name))
							printnl(baseptr == 0 ? "<*>" : "<insert> ");
						else
						{
							printnl("<read ");
							if (txt(name) == 17)
								printchar('*');
							else
								printint(txt(name)-1);
							printchar('>');
						}
					else
					{
						printnl("l.");
						printint(line);
					}
					printchar(' ');
					begin_pseudoprint(l);
					int j;
					if (buffer[limit] == end_line_char())
						j = limit;
					else
						j = limit+1;
					if (j > 0)
						for (int i = start; i < j; i++)
						{
							if (i == loc)
								set_trick_count();
							printchar(buffer[i]);
						}
				}
				else
				{
					switch (token_type)
					{
						case parameter: 
							printnl("<argument> ");
							break;
						case u_template:
						case v_template:
							printnl("<template> ");
							break;
						case backed_up: 
							if (loc == 0)
								printnl("<recently read> ");
							else
								printnl("<to be read again> ");
							break;
						case inserted: 
							printnl("<inserted text> ");
							break;
						case macro:
							println();
							printcs(txt(name));
							break;
						case output_text: 
							printnl("<output> ");
							break;
						case every_par_text: 
							printnl("<everypar> ");
							break;
						case every_math_text: 
							printnl("<everymath> ");
							break;
						case every_display_text: 
							printnl("<everydisplay> ");
							break;
						case every_hbox_text: 
							printnl("<everyhbox> ");
							break;
						case every_vbox_text: 
							printnl("<everyvbox> ");
							break;
						case every_job_text: 
							printnl("<everyjob> ");
							break;
						case every_cr_text: 
							printnl("<everycr> ");
							break;
						case mark_text: 
							printnl("<mark> ");
							break;
						case write_text: 
							printnl("<write> ");
							break;
						default: 
							printnl("?");
					}
					begin_pseudoprint(l);
					if (token_type < macro)
						showtokenlist(start, loc, 100000);
					else
						showtokenlist(link(start), loc, 100000);
				}
				selector = oldsetting;
				if (trickcount == 1000000)
					set_trick_count();
				int m;
				if (tally < trickcount)
					m = tally - firstcount;
				else
					m = trickcount-firstcount;
				int p, n;
				if (l+firstcount <= halferrorline)
				{
					p = 0;
					n = l+firstcount;
				}
				else
				{
					print("...");
					p = l+firstcount-halferrorline+3;
					n = halferrorline;
				}
				for (int q = p; q < firstcount; q++)
					printchar(trickbuf[q%errorline]);
				println();
				for (int q = 0; q < n; q++)
					printchar(' ');
				if (m + n <= errorline)
					p = firstcount+m;
				else
					p = firstcount+errorline-n-3;
				for (int q = firstcount; q < p; q++)
					printchar(trickbuf[q%errorline]);
				if (m+n > errorline)
					print("...");
				nn++;
			}
		}
		else 
			if (nn == error_context_lines())
			{
				printnl("...");
				nn++;
			}
		if (bottomline)
			break;
		baseptr--;
	}
	curinput = inputstack[inputptr];
}

void enddiagnostic(bool blankline)
{
	printnl("");
	if (blankline)
		println();
	selector = oldsetting;
}

//! Prepare to do some tracing
void begindiagnostic(void)
{
	oldsetting = selector;
	if (tracing_online() <= 0 && selector == term_and_log)
	{
		selector--;
		if (history == spotless)
			history = warning_issued;
	}
}

void showcurcmdchr(void)
{
	begindiagnostic();
	printnl("{");
	if (mode != shownmode)
	{
		printmode(mode);
		print(": ");
		shownmode = mode;
	}
	printcmdchr(curcmd, curchr);
	printchar('}');
	enddiagnostic(false);
}

void showactivities(void)
{
	nest[nestptr] = curlist;
	printnl("");
	println();
	for (int p = nestptr; p >= 0; p--)
	{
		int m = nest[p].modefield;
		memoryword a = nest[p].auxfield;
		printnl("### ");
		printmode(m);
		print(" entered at line ");
		printint(abs(nest[p].mlfield));
		if (m == hmode && nest[p].pgfield != 8585216) //0x830000
		{
			print(" (language");
			printint(nest[p].pgfield%0x1'00'00);
			print(":hyphenmin");
			printint(nest[p].pgfield/4194304);
			printchar(',');
			printint((nest[p].pgfield/0x1'00'00)%64);
			printchar(')');
		}
		if (nest[p].mlfield < 0)
			print(" (\\output routine)");
		if (p == 0)
		{
			if (page_head != pagetail)
			{
				printnl("### current page:");
				if (outputactive)
					print(" (held over for link output)");
				showbox(link(page_head));
				if (pagecontents > 0)
				{
					printnl("total height ");
					printtotals();
					printnl(" goal height");
					printscaled(page_goal);
					halfword r = link(page_ins_head);
					while (r != page_ins_head)
					{
						println();
						printesc("insert");
						int t = subtype(r);
						printint(t);
						print(" adds ");
						if (count(t) == 1000)
							t = height(r);
						else
							t = xovern(height(r), 1000)*count(t);
						printscaled(t);
						if (type(r) == vlist_node)
						{
							halfword q = page_head;
							t = 0;
							do
							{
								q = link(q);
								if (type(q) == ins_node && subtype(q) == subtype(r))
									t++;
							} while (q != broken_ins(r));
							print(", #");
							printint(t);
							print(" might split");
						}
						r = link(r);
					}
				}
			}
			;
			if (link(contrib_head))
			printnl("### recent contributions:");
		}
		showbox(link(nest[p].headfield));
		switch (abs(m)/101)
		{
			case 0:
				printnl("prevdepth ");
				if (a.int_ <= -0x1'00'00*1000)
					print("ignored");
				else
					printscaled(a.int_);
				if (nest[p].pgfield)
				{
					print(", prevgraf ");
					printint(nest[p].pgfield);
					print(" line");
					if (nest[p].pgfield != 1)
						printchar('s');
				}
				break;
			case 1:
				printnl("spacefactor ");
				printint(a.hh.lh);
				if (m > 0 && a.hh.rh > 0)
				{
					print(", current language ");
					printint(a.hh.rh);
				}
				break;
			case 2: 
				if (a.int_)
				{
					print("this will be denominator of:");
					showbox(a.int_);
				}
		}
	}
}

void showwhatever(void)
{
	switch (curchr)
	{
		case show_lists:
			begindiagnostic();
			showactivities();
			enddiagnostic(true);
			print_err("OK");
			if (selector == term_and_log && tracing_online() <= 0)
				selector = term_only;
			print(" (see the transcript file)");
			selector = term_and_log;
			break;
		case show_box_code:
			scaneightbitint();
			begindiagnostic();
			printnl("> \\box");
			printint(curval);
			printchar('='); 
			if (box(curval) == 0)
				print("void");
			else
				showbox(box(curval));
			enddiagnostic(true);
			print_err("OK");
			if (selector == term_and_log && tracing_online() <= 0)
				selector = term_only;
			print(" (see the transcript file)");
			selector = term_and_log;
			break;
		case show_code:
			gettoken();
			printnl("> ");
			if (curcs)
			{
				sprintcs(curcs);
				printchar('=');
			}
			printmeaning();
			break;
		default:
			thetoks();
			printnl("> ");
			tokenshow(temp_head);
			flushlist(link(temp_head));
			break;
	}
	if (interaction < error_stop_mode)
	{
		helpptr = 0;
		errorcount--;
	}
	else 
		if (tracing_online() > 0)
		{
			helpptr = 3;
			helpline[2] = "This isn't an error message; I'm just \\showing something.";
			helpline[1] = "Type `I\\show...' to show more (e.g., \\show\\cs,";
			helpline[0] = "\\showthe\\count10, \\showbox255, \\showlists).";
		}
		else
		{
			helpptr = 5;
			helpline[4] = "This isn't an error message; I'm just \\showing something.";
			helpline[3] = "Type `I\\show...' to show more (e.g., \\show\\cs,";
			helpline[2] = "\\showthe\\count10, \\showbox255, \\showlists).";
			helpline[1] = "And type `I\\tracingonline=1\\show...' to show boxes and";
			helpline[0] = "lists on your terminal as well as in the transcript file.";
		}
	error();
}
