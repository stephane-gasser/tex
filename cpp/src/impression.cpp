#include "impression.h"
#include "texte.h"
#include "xovern.h"
#include <iostream> 
#include <cmath>
#include "scaneightbitint.h" 
#include "gettoken.h"
#include "thetoks.h"
#include "flushlist.h"
#include "erreur.h"
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

void slowprint(const std::string &s)
{
	for (auto c: s)
		printchar(c);
}

void print(const std::string &s)
{
	if (txt(s))
	{
		if (s.size() != 1)
		{
			slowprint(s);
			return;
		}
		if (selector > pseudo) // ===new_string
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
		slowprint(s);
		new_line_char() = nl;
	}
	else
		slowprint("???");
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
		auto &cmdNames = primName[cmd];
		if (cmdNames.find(n) != cmdNames.end())
			return esc(cmdNames[n]);
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

static std::string asDelimiter(halfword p)
{
	int a = (mem[p].qqqq.b0<<8)+mem[p].qqqq.b1;
	a = (a<<12)+(mem[p].qqqq.b2<<8)+mem[p].qqqq.b3;
	return a < 0 ? std::to_string(a) : hex(a);
}

std::string esc(const std::string &s) 
{
	auto &c = escape_char();
	if (c >= 0 && c < 256)
		return char(c)+s;
	return s;
}

static std::string famandchar(halfword p)
{
	return esc("fam")+std::to_string(type(p))+" "+TXT(subtype(p));
}

std::string asFilename(const std::string &n, const std::string &a, const std::string &e)
{
	return a+n+e;
}

static std::string fontandchar(int p)
{
	if (p > memend)
		return esc("CLOBBERED.");
	if (type(p) < 0 || type(p) > fontmax)
		return "*"+esc("FONT")+" "+TXT(subtype(p));
	return esc(TXT(text(frozen_null_font+type(p))))+esc("FONT")+" "+TXT(subtype(p));
}

static std::string glue(scaled d, int order, const std::string &s = "")
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

static std::string asMark(int p)
{
	return "{"+(p < himemmin || p > memend ? esc("CLOBBERED.") : tokenlist(link(p), 0, maxprintline-10))+"}";
}

std::string meaning(void)
{
	return cmdchr(curcmd, curchr)+(curcmd >= call ? ":\n"+tokenshow(curchr) : curcmd == top_bot_mark ?":\n"+tokenshow(curmark[curchr]) : "");
}

std::string asMode(int m)
{
	switch (m)
	{
		case vmode: 
			return "vertical mode";
		case hmode: 
			return "horizontal mode";
		case mmode: 
			return "display math mode";
		case -vmode: 
			return "internal vertical mode";
		case -hmode: 
			return "restricted horizontal mode";
		case -mmode: 
			return "math mode";
	}
	return "no mode";
}

void printnl(const std::string &s)
{
	if ((termoffset > 0 && selector%2 == 1) || (fileoffset > 0 && selector >= log_only))
		println();
	print(s);
}


std::string romanint(int n)
{
	constexpr char s[] = "m2d5c2l5x2v5i";
	int j = 0;
	int v = 1000;
	std::ostringstream oss;
	while (true)
	{
		while (n >= v)
		{
			oss << s[j];
			n -= v;
		}
		if (n <= 0)
			return oss.str();
		int k = j+2;
		int u = v/(s[j+1]-'0');
		if (s[j+1] == '2')
		{
			k += 2;
			u /= s[j+3]-'0';
		}
		if (n+u >= v)
		{
			oss << s[k];
			n += u;
		}
		else
		{
			j += 2;
			v /= s[j-1]-'0';
		}
	}
	return oss.str();
}

static std::string ruledimen(scaled d)
{
	if (is_running(d))
		return "*";
	return asScaled(d);
}

std::string asScaled(scaled s)
{
	return std::to_string(double(s)/unity);
}

std::string asSpec(int p, const std::string &s = "")
{
	if (p < memmin || p >= lomemmax)
		return "*";
	return asScaled(width(p))+s+(stretch(p) ? " plus "+glue(stretch(p), type(p), s) : "")+(shrink(p) ? " minus "+glue(shrink(p), subtype(p), s) : "");
}

static std::string shownodelist(halfword p, const std::string &);

//! Display a noad field.
static std::string subsidiarydata(halfword p, char c, const std::string &symbol)
{
	if (cur_length() >= depththreshold)
	{
		if (math_type(p))
			return " []";
		return "";
	}
	std::ostringstream oss;
	switch (math_type(p))
	{
		case math_char:
			oss << "\n" << symbol << c << famandchar(p);
			break;
		case sub_box: 
			oss << shownodelist(info(p), symbol+c);
			break;
		case sub_mlist:
			if (info(p) == 0)
				oss << "\n" << symbol << c << "{}";
			else
				oss << shownodelist(info(p), symbol+c);
	}
	return oss.str();
}

std::string twoDigits(int n)
{
	n = abs(n)%100;
	std::string s;
	s += '0'+n/10;
	s += '0'+n%10;
	return s;
}

static std::string writewhatsit(const std::string &s, halfword p)
{
	return esc(s)+(write_stream(p) < 16 ? std::to_string(write_stream(p)) : write_stream(p) == 16 ? "*" : "-");
}

void slowprint(int s)
{
	if (s >= strptr || s < 256)
		printchar(s);
	else
		for (int j = strstart[s]; j < strstart[s+1]; j++)
			printchar(strpool[j]);
}

void print_err(const std::string &s)
{
	printnl("! "+s);
}

std::string tokenlist(int p, int q, int l)
{
	std::ostringstream oss;
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
			return oss.str()+esc("CLOBBERED.");
		if (info(p) >= cs_token_flag)
			oss << cs(info(p)-cs_token_flag);
		else
		{
			int m = info(p)/0x1'00;
			int c = info(p)%0x1'00;
			if (info(p) < 0)
				oss << esc("BAD.");
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
						oss << char(c);
						break;
					case mac_param:
						oss << char(c) << char(c);
						break;
					case out_param:
						oss << char(matchchr);
						if (c > 9)
							return oss.str()+char('!');
						oss << c;
						break;
					case match:
						matchchr = c;
						oss << char(c) << char(++n);
						if (n > '9')
							return oss.str();
						break;
					case end_match: 
						oss << "->";
						break;
					default:
			  			oss << esc("BAD.");
				}
		}
		p = link(p);
	}
	if (p)
		oss << esc("ETC.");
	return oss.str();
}

std::string tokenshow(halfword p)
{
	return p ? tokenlist(link(p), 0, 10000000) : "";
}

//! a frozen font identifier's name
static halfword& font_id_text(halfword p) { return text(font_id_base+p); }

std::string shortdisplay(int p)
{
	std::ostringstream oss;
	while (p > memmin)
	{
		if (p >= himemmin)
		{
			if (p <= memend)
			{
				if (font(p) != fontinshortdisplay)
				{
					if (font(p) < 0 || font(p) > fontmax)
						oss << "* ";
					else
						oss << esc(TXT(font_id_text(p))) << " ";
					fontinshortdisplay = font(p);
				}
				oss << character(p);
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
					oss << "[]";
					break;
				case rule_node: 
					oss << "|";
					break;
				case glue_node: 
					if (glue_ptr(p) != zero_glue)
						oss << " ";
					break;
				case math_node:
					oss << "$";
					break;
				case ligature_node:
					oss << shortdisplay(lig_ptr(p));
					break;
				case disc_node:
					oss << shortdisplay(pre_break(p)) << shortdisplay(post_break(p));
					for (int n = replace_count(p); n > 0; n--)
						if (link(p))
							p = link(p);
			}
		p = link(p);
	}
	return oss.str();
}

static std::string shownodelist(halfword p, const std::string &symbol)
{
	if (cur_length() > depththreshold)
	{
		if (p > 0)
			return " []";
		return "";
	}
	int n = 0;
	std::ostringstream oss;
	while (p > memmin)
	{
		oss << "\n" << symbol;
		if (p > memend)
			return oss.str()+"Bad link, display aborted.";
		n++;
		if (n > breadthmax)
			return oss.str()+"etc.";
		if (is_char_node(p))
			oss << fontandchar(p);
		else
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
					if (type(p) == hlist_node)
						oss << esc("hbox");
					else 
						if (type(p) == vlist_node)
							oss << esc("vbox");
						else
							oss << esc("unsetbox");
					oss << "(" << asScaled(height(p)) << "+" << asScaled(depth(p)) << ")x" << asScaled(width(p));
					if (type(p) == unset_node)
					{
						if (span_count(p))
							oss << " (" << span_count(p)+1 << " columns)";
						if (glue_stretch(p))
							oss << ", stretch " << glue(glue_stretch(p), glue_order(p));
						if (glue_shrink(p))
							oss << ", shrink " << glue(glue_shrink(p), glue_sign(p));
					}
					else
					{
						g = glue_set(p);
						if (g && glue_sign(p))
						{
							oss << ", glue set ";
							if (glue_sign(p) == shrinking)
								oss << "- ";
							if (!std::isfinite(glue_set(p)))
								oss << "?.?";
							else 
								if (abs(g) > 20000.0)
								{
									if (g > 0.0)
										oss << ">";
									else
										oss << "< -";
									oss << glue(20000*unity, glue_order(p));
								}
								else
									oss << glue(round(unity*g), glue_order(p));
						}
						if (shift_amount(p))
							oss << ", shifted " << asScaled(shift_amount(p));
					}
					shownodelist(list_ptr(p), symbol+".");
					break;
				case rule_node:
					oss << esc("rule") << "(" << ruledimen(width(p)) << "+" << ruledimen(depth(p)) << ")x" << ruledimen(width(p));
					break;
				case ins_node:
					oss << esc("insert") << subtype(p) << ", natural size " << asScaled(height(p)) << "; split("
						<< asSpec(split_top_ptr(p)) << "," << asScaled(depth(p)) << "); float cost " << float_cost(p)
						<< shownodelist(ins_ptr(p), symbol+".");
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case open_node:
							oss << writewhatsit("openout", p) << "=" << asFilename(TXT(open_name(p)), TXT(open_area(p)), TXT(open_ext(p)));
							break;
						case write_node:
							oss << writewhatsit("write", p) << asMark(write_tokens(p));
							break;
						case close_node: 
							oss << writewhatsit("closeout", p); 
							break;
						case special_node:
							oss << esc("special") << asMark(write_tokens(p));
							break;
						case language_node:
							oss << esc("setlanguage") <<what_lang(p) << " (hyphenmin" << what_lhm(p) << "," << what_rhm(p) << ")";
							break;
						default: 
							oss << "whatsit?";
					}
					break;
				case glue_node:
					if (subtype(p) >= a_leaders)
						oss << esc(subtype(p) == c_leaders ? "cleaders" : subtype(p) == x_leaders ? "xleaders" : "leaders ") 
							<< asSpec(glue_ptr(p)) << shownodelist(leader_ptr(p), symbol+".");
					else
					{
						oss << esc("glue");
						int n = subtype(p)-1;
						auto &glueNames = primName[assign_glue];
						auto &muGlueNames = primName[assign_mu_glue];
						switch (n+1)
						{
							case normal:
								oss << esc("glue") << " " << asSpec(glue_ptr(p));
								break;
							case cond_math_glue:
								oss << esc("glue") << "(" << esc("nonscript") << ")";
								break;
							case mu_glue:
								oss << esc("glue") << "(" << esc("mskip") << ") " << asSpec(glue_ptr(p), "mu");
								break;
							default:
								if (glueNames.find(n) != glueNames.end())
								{
									oss << esc("glue") << "(" << esc(glueNames[n]) << ") " << asSpec(glue_ptr(p));
									break;
								}
								if (muGlueNames.find(n) != muGlueNames.end())
								{
									oss << esc("glue") << "(" << esc(muGlueNames[n]) << ") " << asSpec(glue_ptr(p));
									break;
								}
								oss << esc("glue") << "(" << "[unknown glue parameter!]" << ") " << asSpec(glue_ptr(p));
						}
					}
				case kern_node:
					switch(subtype(p))
					{
						case normal:
							oss << esc("kern") << asScaled(width(p));
							break;
						case mu_glue:
							oss << esc("mkern") << asScaled(width(p)) << "mu";
							break;
						case acc_kern:
							oss << esc("kern") << " " << asScaled(width(p)) << " (for accent)";
							break;
						default:
							oss << esc("kern") << " " << asScaled(width(p));
					}
					break;
				case math_node:
					oss << esc("math") << (subtype(p) == before ? "on" : "off");
					if (width(p))
						oss << ", surrounded " << asScaled(width(p));
					break;
				case ligature_node:
					oss << fontandchar(lig_char(p)) << " (ligature ";
					if (subtype(p) > 1)
						oss << "|";
					fontinshortdisplay = font(lig_char(p));
					oss << shortdisplay(lig_char(p));
					if (subtype(p)%2)
						oss << "|";
					oss << ")";
					break;
				case penalty_node:
					oss << esc("penalty ") << penalty(p);
					break;
				case disc_node:
					oss << esc("discretionary");
					if (subtype(p) > 0)
						oss << " replacing " << subtype(p);
					oss << shownodelist(pre_break(p), symbol+".");
					oss << shownodelist(post_break(p), symbol+"|");
					break;
				case mark_node:
					oss << esc("mark") << asMark(mark_ptr(p));
					break;
				case adjust_node:
					oss << esc("vadjust") << shownodelist(adjust_ptr(p), symbol+".");
					break;
				case style_node:
					if (primName[math_style].find(subtype(p)) != primName[math_style].end())
						oss << esc(primName[math_style][subtype(p)]);
					else
						oss << "Unknown style!";
					break;
				case choice_node:
					oss << esc("mathchoice");
					oss << shownodelist(display_mlist(p), symbol+"D");
					oss << shownodelist(text_mlist(p), symbol+"T");
					oss << shownodelist(script_mlist(p), symbol+"S");
					oss << shownodelist(script_script_mlist(p), symbol+"s");
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
							oss << esc("mathord");
							break;
						case op_noad: 
							oss << esc("mathop");
							break;
						case bin_noad: 
							oss << esc("mathbin");
							break;
						case rel_noad: 
							oss << esc("mathrel");
							break;
						case open_noad: 
							oss << esc("mathopen");
							break;
						case close_noad: 
							oss << esc("mathclose");
							break;
						case punct_noad: 
							oss << esc("mathpunct");
							break;
						case inner_noad: 
							oss << esc("mathinner");
							break;
						case over_noad: 
							oss << esc("overline");
							break;
						case under_noad: 
							oss << esc("underline");
							break;
						case vcenter_noad: 
							oss << esc("vcenter");
							break;
						case radical_noad:
							oss << esc("radical") << asDelimiter(left_delimiter(p));
							break;
						case accent_noad:
							oss << esc("accent") << famandchar(accent_chr(p));
							break;
						case left_noad:
							oss << esc("left") << asDelimiter(delimiter(p));
							break;
						case right_noad:
							oss << esc("right") << asDelimiter(delimiter(p));
					}
					if (subtype(p))
						if (subtype(p) == limits)
							oss << esc("limits");
						else
							oss << esc("nolimits");
					if (type(p) < left_noad)
						oss << subsidiarydata(nucleus(p), '.', symbol);
					oss << subsidiarydata(supscr(p), '^', symbol);
					oss << subsidiarydata(subscr(p), '_', symbol);
					break;
				case fraction_noad:
					oss << esc("fraction, thickness ") << (new_hlist(p) == default_code ? "= default": asScaled(new_hlist(p)));
					if (small_fam(left_delimiter(p))
					 || small_char(left_delimiter(p))
					 || large_fam(left_delimiter(p))
					 || large_char(left_delimiter(p)))
						oss << ", left-delimiter " << asDelimiter(left_delimiter(p));
					if (small_fam(right_delimiter(p))
					 || small_char(right_delimiter(p))
					 || large_fam(right_delimiter(p))
					 || large_char(right_delimiter(p)))
						oss << ", right-delimiter " << asDelimiter(right_delimiter(p));
					oss << subsidiarydata(numerator(p), '\\', symbol);
					oss << subsidiarydata(denominator(p), '/', symbol);
					break;
				default: 
					oss << "Unknown node type!";
			}
		p = link(p);
	}
	return oss.str();
}

static int show_box_breadth(void) { return int_par(show_box_breadth_code); }
static int show_box_depth(void) { return int_par(show_box_depth_code); }

std::string showbox(halfword p)
{  
	depththreshold = std::min(show_box_depth(), poolsize-poolptr-1);
	breadthmax = show_box_breadth();
	if (breadthmax <= 0)
		breadthmax = 5;
	return shownodelist(p, "")+"\n";
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

std::string showcontext(void)
{
	int l;
	baseptr = inputptr;
	inputstack[baseptr] = curinput; 
	int nn = -1;
	bool bottomline = false;
	std::ostringstream oss;
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
							oss << (baseptr == 0 ? "\r<*> " : "\r<insert>  ");
						else
							oss << ("\r<read "+(txt(name) == 17 ? "*" : std::to_string((txt(name)-1)))+"> ");
					else
						oss << "\rl."+std::to_string(line) << " ";
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
							oss << buffer[i];
						}
				}
				else
				{
					switch (token_type)
					{
						case parameter: 
							oss << "\r<argument> ";
							break;
						case u_template:
						case v_template:
							oss << "\r<template> ";
							break;
						case backed_up: 
							if (loc == 0)
								oss << "\r<recently read> ";
							else
								oss << "\r<to be read again> ";
							break;
						case inserted: 
							oss << "\r<inserted text> ";
							break;
						case macro:
							oss << "\n" << cs(txt(name));
							break;
						case output_text: 
							oss << "\r<output> ";
							break;
						case every_par_text: 
							oss << "\r<everypar> ";
							break;
						case every_math_text: 
							oss << "\r<everymath> ";
							break;
						case every_display_text: 
							oss << "\r<everydisplay> ";
							break;
						case every_hbox_text: 
							oss << "\r<everyhbox> ";
							break;
						case every_vbox_text: 
							oss << "\r<everyvbox> ";
							break;
						case every_job_text: 
							oss << "\r<everyjob> ";
							break;
						case every_cr_text: 
							oss << "\r<everycr> ";
							break;
						case mark_text: 
							oss << "\r<mark> ";
							break;
						case write_text: 
							oss << "\r<write> ";
							break;
						default: 
							oss << "\r?";
					}
					begin_pseudoprint(l);
					oss << (token_type < macro ? tokenlist(start, loc, 100000): tokenlist(link(start), loc, 100000));
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
					oss <<"...";
					p = l+firstcount-halferrorline+3;
					n = halferrorline;
				}
				for (int q = p; q < firstcount; q++)
					oss << trickbuf[q%errorline];
				oss << "\n";
				for (int q = 0; q < n; q++)
					oss << " ";
				if (m + n <= errorline)
					p = firstcount+m;
				else
					p = firstcount+errorline-n-3;
				for (int q = firstcount; q < p; q++)
					oss << trickbuf[q%errorline];
				if (m+n > errorline)
					oss << "...";
				nn++;
			}
		}
		else 
			if (nn == error_context_lines())
			{
				oss << "\r...";
				nn++;
			}
		if (bottomline)
			break;
		baseptr--;
	}
	curinput = inputstack[inputptr];
	return oss.str();
}

std::string enddiagnostic(bool blankline)
{
	std::ostringstream oss;
	if (blankline)
		oss << "\n";
	selector = oldsetting;
	return oss.str();
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
	printnl("{"+(mode != shownmode ? asMode(mode)+": " : "")+cmdchr(curcmd, curchr)+"}");
	shownmode = mode;
	print(enddiagnostic(false));
}

static std::string plus(int i, const std::string &s)
{
	if (pagesofar[i])
		return " plus "+asScaled(pagesofar[i])+s;
	return "";
}

static void showactivities(void)
{
	nest[nestptr] = curlist;
	printnl("\n");
	for (int p = nestptr; p >= 0; p--)
	{
		int m = nest[p].modefield;
		memoryword a = nest[p].auxfield;
		printnl("### "+asMode(m)+" entered at line "+std::to_string(abs(nest[p].mlfield)));
		if (m == hmode && nest[p].pgfield != (2<<22)+(3<<16)+0) // language=0, hyphenmin=2,3
			print(" (language"+std::to_string(nest[p].pgfield%(1<<16))+":hyphenmin"+std::to_string(nest[p].pgfield>>22)+","+std::to_string((nest[p].pgfield>>16)%(1<<6))+")");
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

static void erreurShowwhatever1(void)
{
	helpptr = 0;
	error();
}

static void erreurShowwhatever2(void)
{
	helpptr = 3;
	helpline[2] = "This isn't an error message; I'm just \\showing something.";
	helpline[1] = "Type `I\\show...' to show more (e.g., \\show\\cs,";
	helpline[0] = "\\showthe\\count10, \\showbox255, \\showlists).";
	error();
}

static void erreurShowwhatever3(void)
{
	helpptr = 5;
	helpline[4] = "This isn't an error message; I'm just \\showing something.";
	helpline[3] = "Type `I\\show...' to show more (e.g., \\show\\cs,";
	helpline[2] = "\\showthe\\count10, \\showbox255, \\showlists).";
	helpline[1] = "And type `I\\tracingonline=1\\show...' to show boxes and";
	helpline[0] = "lists on your terminal as well as in the transcript file.";
	error();
}

void showwhatever(void)
{
	switch (curchr)
	{
		case show_lists:
			begindiagnostic();
			showactivities();
			print(enddiagnostic(true));
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
			print(enddiagnostic(true));
			print_err("OK");
			if (selector == term_and_log && tracing_online() <= 0)
				selector = term_only;
			print(" (see the transcript file)");
			selector = term_and_log;
			break;
		case show_code:
			gettoken();
			printnl("> "+(curcs ? scs(curcs)+"=" : "")+meaning());
			break;
		default:
			thetoks();
			printnl("> "+tokenshow(temp_head));
			flushlist(link(temp_head));
			break;
	}
	if (interaction < error_stop_mode)
	{
		erreurShowwhatever1();
		errorcount--;
	}
	else 
		if (tracing_online() > 0)
			erreurShowwhatever2();
		else
			erreurShowwhatever3();
}
