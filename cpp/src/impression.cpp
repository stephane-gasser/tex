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
#include "primitive.h"
#include <sstream>

static void printchar(ASCIIcode s)
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

static std::string chr_cmd(const std::string &s, halfword chrcode)
{
	return s+char(chrcode);
}

static std::string hex(int t)
{
  std::ostringstream oss;
  oss << "\"" << std::hex << t;
  return oss.str();
}

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

std::string cmdchr(quarterword cmd, halfword chrcode)
{
	static std::map<quarterword, std::string> echap;
	static std::map<quarterword, std::string> caract;
	if (!echap.size())
	{
		echap[long_call] = "long macro";
		echap[outer_call] = "outer macro";
		echap[long_outer_call] = "long"+esc("outer macro");
		echap[end_template] = "outer endtemplate";
		caract[left_brace] = "begin-group character ";
		caract[right_brace] = "end-group character ";
		caract[math_shift] = "math shift character ";
		caract[mac_param] = "macro parameter character ";
		caract[sup_mark] = "superscript character ";
		caract[sub_mark] = "subscript character ";
		caract[spacer] = "blank space ";
		caract[letter] = "the letter ";
		caract[other_char] = "the character ";
		caract[tab_mark] = "alignment tab character ";
	}
	if (primName.find(cmd) != primName.end())
	{
		int n = curchr;
		switch (cmd)
		{
			case assign_glue:
			case assign_mu_glue:
				n -= glue_base;
				break;
			case assign_int:
				n -= int_base;
				break;
			case assign_dimen:
				n -= dimen_base;
				break;
			case def_family:
				n -= math_font_base;
		}
		if (primName[cmd].find(n) != primName[cmd].end())
			return esc(primName[cmd][n]);
	}
	switch (cmd)
	{
		case long_call: 
		case outer_call: 
		case long_outer_call:
		case end_template: 
			return esc(echap[cmd]);
		case assign_glue:
			if (chrcode < skip_base)
				return "[unknown glue parameter!]";
			return esc("skip")+std::to_string(chrcode-skip_base);
		case assign_mu_glue:
			if (chrcode < mu_skip_base)
				return "[unknown glue parameter!]";
			return esc("muskip")+std::to_string(chrcode-mu_skip_base);
		case assign_toks:
			return esc("toks")+std::to_string(chrcode-toks_base);
		case assign_int: 
			if (chrcode < count_base)
				return "[unknown integer parameter!]";
			return esc("count")+std::to_string(chrcode-count_base);
		case assign_dimen:
			if (chrcode < scaled_base)
				return "[unknown dimen parameter!]";
			return esc("dimen")+std::to_string(chrcode-scaled_base);
		case char_given:
			return esc("char")+hex(chrcode);
		case math_given:
			return esc("mathchar")+hex(chrcode); 
		case set_font:
			return "select font "+fontname[chrcode]+(fontsize[chrcode] == fontdsize[chrcode] ? "" : " at "+std::to_string(double(fontsize[chrcode])/unity)+"pt");
		case tab_mark:
		case left_brace:
		case right_brace:
		case math_shift:
		case mac_param:
		case sup_mark:
		case sub_mark:
		case spacer:
		case letter:
		case other_char:
			return chr_cmd(caract[cmd], chrcode);
		case math_style:
			return "Unknown style!";
		case extension: 
			return "[unknown extension!]";
		case endv:
			return "end of alignment template";
		case undefined_cs:
			return "undefined";
		case call: 
			return "macro";
	}
	return "[unknown command code!]";
}

std::string cs(int p)
{
	if (p < hash_base)
	{
		if (p >= single_base)
		{
			if (p == null_cs)
				return esc("csname")+esc("endcsname")+" ";
			return esc(std::string(1, p-single_base))+(cat_code(p-single_base) == letter ? " " : "");
		}
		if (p < active_base)
			return esc("IMPOSSIBLE.");
		return std::string(1, p-active_base);
	}
	if (p >= undefined_control_sequence)
		return esc("IMPOSSIBLE.");
	if (text(p) < 0 || text(p) >= strptr)
		return esc("NONEXISTENT.");
	return esc(TXT(hash[p].rh))+" ";
}

std::string scs(halfword p)
{
	if (p < hash_base)
	{
		if (p >= single_base)
		{
			if (p >= null_cs)
				return esc("csname")+esc("endcsname");
			return esc(std::string(1, p-single_base));
		}
		return std::string(1, p-active_base);
	}
	return esc(TXT(text(p)));
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
	print(a < 0 ? std::to_string(a) : hex(a));
}

std::string esc(const std::string &s) 
{
	auto &c = escape_char();
	if (c >= 0 && c < 256)
		return char(c)+s;
	return s;
}

void printfamandchar(halfword p)
{
	print(esc("fam")+std::to_string(type(p))+" "+TXT(subtype(p)));
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
		print(esc("CLOBBERED."));
	else
	{
		if (type(p) < 0 || type(p) > fontmax)
			printchar('*');
		else
			print(esc(TXT(text(frozen_null_font+type(p)))));
		print(esc("FONT")+" "+TXT(subtype(p)));
	}
}

static std::string glue(scaled d, int order, const std::string &s)
{
	if (order < 0 || order > 3)
		return asScaled(d)+"foul";
	if (order > 0)
		return asScaled(d)+"fi"+std::string(order, 'l');
	if (txt(s))
		return s;
	return "";
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
		print(esc("CLOBBERED."));
	else
		showtokenlist(link(p), 0, maxprintline-10);
	printchar('}');
}

void printmeaning(void)
{
	print(cmdchr(curcmd, curchr));
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
		print(asScaled(d));
}

std::string asScaled(scaled s)
{
	return std::to_string(double(s)/unity);
}

void printspec(int p, const std::string &s)
{
	if (p < memmin || p >= lomemmax)
		printchar('*');
	else
	{
		print(asScaled(width(p)));
		if (s != "")
			print(s);
		if (stretch(p))
			print(" plus "+glue(stretch(p), type(p), s));
		if (shrink(p))
			print(" minus "+glue(shrink(p), subtype(p), s));
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

void printtwo(int n)
{
	n = abs(n)%100;
	printchar('0'+n/10);
	printchar('0'+n%10);
}

void printwritewhatsit(const std::string &s, halfword p)
{
	print(esc(s)+(write_stream(p) < 16 ? std::to_string(write_stream(p)) :write_stream(p) == 16 ? "*" : "-"));
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

void print_err(const std::string &s)
{
	printnl("! "+s);
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
			print(esc("CLOBBERED."));
			return;
		}
		if (info(p) >= cs_token_flag)
			print(cs(info(p)-cs_token_flag));
		else
		{
			int m = info(p)/0x1'00;
			int c = info(p)%0x1'00;
			if (info(p) < 0)
				print(esc("BAD."));
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
			  			print(esc("BAD."));
				}
		}
		p = link(p);
	}
	if (p)
		print(esc("ETC."));
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
						print(esc(TXT(font_id_text(p))));
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
						print(esc("hbox"));
					else 
						if (type(p) == vlist_node)
							print(esc("vbox"));
						else
							print(esc("unsetbox"));
					print("("+asScaled(height(p))+"+"+asScaled(depth(p))+")x"+asScaled(width(p)));
					if (type(p) == unset_node)
					{
						if (span_count(p))
							print(" ("+std::to_string(span_count(p)+1)+" columns)");
						if (glue_stretch(p))
							print(", stretch "+glue(glue_stretch(p), glue_order(p), ""));
						if (glue_shrink(p))
							print(", shrink "+glue(glue_shrink(p), glue_sign(p), ""));
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
									print(glue(20000*unity, glue_order(p), ""));
								}
								else
									print(glue(round(unity*g), glue_order(p), ""));
						}
						if (shift_amount(p))
							print(", shifted "+asScaled(shift_amount(p)));
					}
					node_list_display(list_ptr(p));
					break;
				case rule_node:
					print(esc("rule")+"(");
					printruledimen(width(p));
					printchar('+');
					printruledimen(depth(p));
					print(")x");
					printruledimen(width(p));
					break;
				case ins_node:
					print(esc("insert")+std::to_string(subtype(p))+", natural size "+asScaled(height(p))+"; split(");
					printspec(split_top_ptr(p), 0);
					print(","+asScaled(depth(p))+"); float cost "+std::to_string(float_cost(p)));
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
							print(esc("special"));
							printmark(link(p+1));
							break;
						case 4:
							print(esc("setlanguage")+std::to_string(what_lang(p))+" (hyphenmin"+std::to_string(what_lhm(p))+","+std::to_string(what_rhm(p))+")");
							break;
						default: 
							print("whatsit?");
					}
					break;
				case glue_node:
					if (subtype(p) >= a_leaders)
					{
						print(esc(subtype(p) == c_leaders ? "cleaders" : subtype(p) == x_leaders ? "xleaders" : "leaders "));
						printspec(glue_ptr(p), 0);
						node_list_display(leader_ptr(p));
					}
					else
					{
						print(esc("glue"));
						if (subtype(p) != normal)
						{
							printchar('(');
							if (subtype(p) < cond_math_glue)
							{
								int n = subtype(p)-1;
								if (primName[assign_glue].find(n) != primName[assign_glue].end())
										print(esc(primName[assign_glue][n]));
									else 
										if (primName[assign_mu_glue].find(n) != primName[assign_mu_glue].end())
											print(esc(primName[assign_mu_glue][n]));
										else
											print("[unknown glue parameter!]");
							
							}
							else 
								if (subtype(p) == cond_math_glue)
								print(esc("nonscript"));
							else
								print(esc("mskip"));
							printchar(')');
						}
						if (subtype(p) != cond_math_glue)
						{
							printchar(' ');
							if (subtype(p) < cond_math_glue)
								printspec(glue_ptr(p), 0);
							else
								printspec(glue_ptr(p), "mu");
						}
					}
				case kern_node:
					if (subtype(p) != mu_glue)
					{
						print(esc("kern"));
						if (subtype(p) != normal)
							printchar(' ');
						print(asScaled(width(p)));
						if (subtype(p) == acc_kern)
							print(" (for accent)");
					}
					else
						print(esc("mkern")+asScaled(width(p))+"mu");
					break;
				case math_node:
					print(esc("math"));
					if (subtype(p) == before)
						print("on");
					else
						print("off");
					if (width(p))
						print(", surrounded "+asScaled(width(p)));
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
					print(esc("penalty ")+std::to_string(penalty(p)));
					break;
				case disc_node:
					print(esc("discretionary"));
					if (subtype(p) > 0)
					{
						print(" replacing "+std::to_string(subtype(p)));
					}
					node_list_display(pre_break(p));
					append_char('|');
					shownodelist(post_break(p));
					flush_char();
					break;
				case mark_node:
					print(esc("mark"));
					printmark(mark_ptr(p));
					break;
				case adjust_node:
					print(esc("vadjust"));
					node_list_display(adjust_ptr(p));
					break;
				case style_node: 
					if (primName[math_style].find(subtype(p)) != primName[math_style].end())
						print(esc(primName[math_style][subtype(p)]));
					else
						print("Unknown style!");
					break;
				case choice_node:
					print(esc("mathchoice"));
					append_char('D');
					shownodelist(display_mlist(p));
					flush_char();
					append_char('T');
					shownodelist(text_mlist(p));
					flush_char();
					append_char('S');
					shownodelist(script_mlist(p));
					flush_char();
					append_char('s');
					shownodelist(script_script_mlist(p));
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
							print(esc("mathord"));
							break;
						case op_noad: 
							print(esc("mathop"));
							break;
						case bin_noad: 
							print(esc("mathbin"));
							break;
						case rel_noad: 
							print(esc("mathrel"));
							break;
						case open_noad: 
							print(esc("mathopen"));
							break;
						case close_noad: 
							print(esc("mathclose"));
							break;
						case punct_noad: 
							print(esc("mathpunct"));
							break;
						case inner_noad: 
							print(esc("mathinner"));
							break;
						case over_noad: 
							print(esc("overline"));
							break;
						case under_noad: 
							print(esc("underline"));
							break;
						case vcenter_noad: 
							print(esc("vcenter"));
							break;
						case radical_noad:
							print(esc("radical"));
							printdelimiter(left_delimiter(4));
							break;
						case accent_noad:
							print(esc("accent"));
							printfamandchar(accent_chr(p));
							break;
						case left_noad:
							print(esc("left"));
							printdelimiter(delimiter(p));
							break;
						case right_noad:
							print(esc("right"));
							printdelimiter(delimiter(p));
					}
					if (subtype(p))
						if (subtype(p) == limits)
							print(esc("limits"));
						else
							print(esc("nolimits"));
					if (type(p) < left_noad)
						printsubsidiarydata(nucleus(p), '.');
					printsubsidiarydata(supscr(p), '^');
					printsubsidiarydata(subscr(p), '_');
					break;
				case fraction_noad:
					print(esc("fraction, thickness "));
					if (new_hlist(p) == default_code)
						print("= default");
					else
						print(asScaled(new_hlist(p)));
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
							printnl("<read "+ (txt(name) == 17 ? "*" : std::to_string((txt(name)-1)))+">");
					else
						printnl("l."+std::to_string(line));
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
							print(cs(txt(name)));
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
	}
	shownmode = mode;
	print(cmdchr(curcmd, curchr)+"}");
	enddiagnostic(false);
}

static std::string plus(int i, const std::string &s)
{
	if (pagesofar[i])
		return " plus "+asScaled(pagesofar[i])+s;
	return "";
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
		print(" entered at line "+std::to_string(abs(nest[p].mlfield)));
		if (m == hmode && nest[p].pgfield != 8585216) //0x830000
			print(" (language"+std::to_string(nest[p].pgfield%0x1'00'00)+":hyphenmin"+std::to_string(nest[p].pgfield/4194304)+","+std::to_string((nest[p].pgfield/0x1'00'00)%64)+")");
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
					printnl("total height "+asScaled(page_total)+plus(2, "")+plus(3, "fil")+plus(4, "fill")+plus(5, "filll")+(page_shrink ? " minus "+asScaled(page_shrink) : ""));
					printnl(" goal height");
					print(asScaled(page_goal));
					halfword r = link(page_ins_head);
					while (r != page_ins_head)
					{
						println();
						print(esc("insert")+std::to_string(subtype(r))+" adds "+asScaled(count(subtype(r)) == 1000 ? height(r) : xovern(height(r), 1000)*count(subtype(r))));
						if (type(r) == vlist_node)
						{
							halfword q = page_head;
							int t = 0;
							do
							{
								q = link(q);
								if (type(q) == ins_node && subtype(q) == subtype(r))
									t++;
							} while (q != broken_ins(r));
							print(", #"+std::to_string(t)+" might split");
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
				printnl("prevdepth "+(a.int_ <= ignore_depth ? "ignored" : asScaled(a.int_)));
				if (nest[p].pgfield)
					print(", prevgraf "+std::to_string(nest[p].pgfield)+" line"+(nest[p].pgfield == 1 ?"" : "s"));
				break;
			case 1:
				printnl("spacefactor "+std::to_string(a.hh.lh));
				if (m > 0 && a.hh.rh > 0)
					print(", current language "+std::to_string(a.hh.rh));
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
			printnl("> \\box"+std::to_string(curval)+"="); 
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
			printnl("> "+(curcs ? scs(curcs)+"=" : ""));
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
