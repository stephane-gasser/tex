#include "impression.h"
#include "texte.h"
#include "xovern.h"
#include <iostream> 
#include <cmath>
#include "lecture.h" 
#include "noeud.h"
#include "erreur.h"
#include "primitive.h"
#include "police.h"
#include "equivalent.h"
#include <sstream> 

static int tally = 0;

static void printchar(ASCIIcode s)
{
	if (s == new_line_char())
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
		default: 
			writefile[selector] << xchr[s];
	}
	tally++;
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
		unsigned char S = s[0];
		if (S == new_line_char())
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

std::string cmdchr(Token t)
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
	if (primName.find(t.cmd) != primName.end())
	{
		int n = t.chr;
		switch (t.cmd)
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
		auto &cmdNames = primName[t.cmd];
		if (cmdNames.find(n) != cmdNames.end())
			return esc(cmdNames[n]);
	}
	switch (t.cmd)
	{
		case long_call: 
		case outer_call: 
		case long_outer_call:
		case end_template: 
			return esc(echap[t.cmd]);
		case assign_glue:
			if (t.chr < skip_base)
				return "[unknown glue parameter!]";
			return esc("skip")+std::to_string(t.chr-skip_base);
		case assign_mu_glue:
			if (t.chr < mu_skip_base)
				return "[unknown glue parameter!]";
			return esc("muskip")+std::to_string(t.chr-mu_skip_base);
		case assign_toks:
			return esc("toks")+std::to_string(t.chr-toks_base);
		case assign_int: 
			if (t.chr < count_base)
				return "[unknown integer parameter!]";
			return esc("count")+std::to_string(t.chr-count_base);
		case assign_dimen:
			if (t.chr < scaled_base)
				return "[unknown dimen parameter!]";
			return esc("dimen")+std::to_string(t.chr-scaled_base);
		case char_given:
			return esc("char")+hex(t.chr);
		case math_given:
			return esc("mathchar")+hex(t.chr); 
		case set_font:
			return "select font "+fonts[t.chr].name+(fonts[t.chr].size == fonts[t.chr].dsize ? "" : " at "+std::to_string(double(fonts[t.chr].size)/unity)+"pt");
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
			return caract[t.cmd]+char(t.chr);
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
	return esc(eqtb_cs[p-hash_base].text)+" ";
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
	return esc(eqtb_cs[p-hash_base].text);
}

static std::string asDelimiter(Delimiter p)
{
	int a = (p.small_fam<<20)+(p.small_char<<12)+(p.large_fam<<8)+p.large_char;
	return a < 0 ? std::to_string(a) : hex(a);
}

std::string esc(const std::string &s) 
{
	auto &c = escape_char();
	if (c >= 0 && c < 256)
		return char(c)+s;
	return s;
}

static std::string famandchar(const NoadContent &p)
{
	return esc("fam")+std::to_string(p.fam)+" "+TXT(p.character);
}

std::string asFilename(const std::string &n, const std::string &a, const std::string &e)
{
	return a+n+e;
}

static std::string fontandchar(CharNode *p)
{
/*	if (p > memend)
		return esc("CLOBBERED.");*/
	if (&p->font == nullptr)
		return "*"+esc("FONT")+" "+char(p->character);
	return esc(p->font.name)+esc("FONT")+" "+char(p->character);
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
		default: 
			writefile[selector] << "\n";
	}
}

static std::string asMark(TokenNode *p)
{
	return "{"+(/*p < himemmin || p > memend ? esc("CLOBBERED.") :*/ tokenlist(dynamic_cast<TokenNode*>(p->link), nullptr, maxprintline-10))+"}";
}

std::string meaning(Token t) 
{
	TokenNode T(t.chr);
	return cmdchr(t)+(t.cmd >= call ? ":\n"+tokenshow(&T) : t.cmd == top_bot_mark ?":\n"+tokenshow(curmark[t.chr]) : ""); 
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

std::string asSpec(GlueSpec *p, const std::string &s = "")
{
/*	if (p < memmin || p >= lomemmax)
		return "*";*/
	return asScaled(p->width)+s+(p->stretch ? " plus "+glue(p->stretch, p->stretch_order, s) : "")+(p->shrink ? " minus "+glue(p->shrink, p->shrink_order, s) : "");
}

static std::string shownodelist(LinkedNode*, const std::string &);

//! Display a noad field.
static std::string subsidiarydata(const NoadContent &p, char c, const std::string &symbol)
{
	if (cur_length() >= depththreshold)
	{
		if (p.math_type)
			return " []";
		return "";
	}
	std::ostringstream oss;
	switch (p.math_type)
	{
		case math_char:
			oss << "\n" << symbol << c << famandchar(p);
			break;
		case sub_box: 
			oss << shownodelist(p.info, symbol+c);
			break;
		case sub_mlist:
			if (p.info == nullptr)
				oss << "\n" << symbol << c << "{}";
			else
				oss << shownodelist(p.info, symbol+c);
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

static std::string writewhatsit(const std::string &s, WriteWhatsitNode *p)
{
	return esc(s)+(p->write_stream < 16 ? std::to_string(p->write_stream) : p->write_stream == 16 ? "*" : "-");
}

void slowprint(int s)
{
	if (s >= strings.size() || s < 256)
		printchar(s);
	else
		print(strings[s]);
}

void print_err(const std::string &s)
{
	printnl("! "+s);
}

std::string tokenlist(TokenNode *p, TokenNode *q, int l)
{
	std::ostringstream oss;
	ASCIIcode matchchr = '#';
	ASCIIcode n = '0';
	while (p && oss.str().size() < l)
	{
		if (p == q)
		{
			firstcount = oss.str().size();
			trickcount = std::max(firstcount+1+errorline-halferrorline, errorline);
		}
/*		if (p < himemmin || p > memend)
			return oss.str()+esc("CLOBBERED.");*/
		if (p->token >= cs_token_flag)
			oss << cs(p->token-cs_token_flag);
		else
		{
			int m = p->token>>8;
			int c = p->token%(1<<8);
			if (p->token < 0)
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
		p = dynamic_cast<TokenNode*>(p->link);
	}
	if (p)
		oss << esc("ETC.");
	return oss.str();
}

std::string tokenshow(TokenNode *p)
{
	return p ? tokenlist(dynamic_cast<TokenNode*>(p->link), 0, 10000000) : "";
}

//static halfword& font_id_text(halfword p) { return text(font_id_base+p); } //! a frozen font identifier's name

std::string shortdisplay(LinkedNode *p)
{
	std::ostringstream oss;
	for (; p; next(p))
		if (p->is_char_node())
		{
			if (/*p <= memend*/true)
			{
				auto pp = dynamic_cast<CharNode*>(p);
				if (pp->font != fontinshortdisplay)
				{
					if (/*pp->font < 0 || pp->font > fontmax*/true)
						oss << "* ";
					else
						oss << esc(pp->font.name) << " ";
					fontinshortdisplay = pp->font;
				}
				oss << pp->character;
			}
		}
		else
			switch (p->type)
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
					if (dynamic_cast<GlueNode*>(p)->glue_ptr != /*zero_glue*/nullptr)
						oss << " ";
					break;
				case math_node:
					oss << "$";
					break;
				case ligature_node:
					oss << shortdisplay(dynamic_cast<LigatureNode*>(p)->lig_ptr);
					break;
				case disc_node:
				{
					auto d = dynamic_cast<DiscNode*>(p);
					oss << shortdisplay(d->pre_break) << shortdisplay(d->post_break);
					LinkedNode *q = d;
					for (int n = d->replace_count; n > 0; n--)
						if (q->link)
							next(q);
				}
			}
	return oss.str();
}

static std::string shownodelist(LinkedNode *p, const std::string &symbol)
{
	if (cur_length() > depththreshold)
	{
		if (p > 0)
			return " []";
		return "";
	}
	int n = 0;
	std::ostringstream oss;
	while (/*p > memmin*/true)
	{
		oss << "\n" << symbol;
		/*if (p > memend)
			return oss.str()+"Bad link, display aborted.";*/
		n++;
		if (n > breadthmax)
			return oss.str()+"etc.";
		if (p->is_char_node())
			oss << fontandchar(dynamic_cast<CharNode*>(p));
		else
			switch (p->type)
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
				{
					auto P = dynamic_cast<BoxNode*>(p);
					if (p->type == hlist_node)
						oss << esc("hbox");
					else 
						if (p->type == vlist_node)
							oss << esc("vbox");
						else
							oss << esc("unsetbox");
					oss << "(" << asScaled(P->height) << "+" << asScaled(P->depth) << ")x" << asScaled(P->width);
					if (p->type == unset_node)
					{
						auto P = dynamic_cast<UnsetNode*>(p);
						if (P->span_count)
							oss << " (" << P->span_count+1 << " columns)";
						if (P->glue_stretch)
							oss << ", stretch " << glue(P->glue_stretch, P->glue_order);
						if (P->glue_shrink)
							oss << ", shrink " << glue(P->glue_shrink, P->glue_sign);
					}
					else
					{
						auto g = P->glue_set;
						if (g && P->glue_sign)
						{
							oss << ", glue set ";
							if (P->glue_sign == shrinking)
								oss << "- ";
							if (!std::isfinite(P->glue_set))
								oss << "?.?";
							else 
								if (abs(g) > 20000.0)
								{
									if (g > 0.0)
										oss << ">";
									else
										oss << "< -";
									oss << glue(20000*unity, P->glue_order);
								}
								else
									oss << glue(round(unity*g), P->glue_order);
						}
						if (P->shift_amount)
							oss << ", shifted " << asScaled(P->shift_amount);
					}
					shownodelist(P->list_ptr, symbol+".");
					break;
				}
				case rule_node:
				{
					auto P = dynamic_cast<RuleNode*>(p);
					oss << esc("rule") << "(" << ruledimen(P->width) << "+" << ruledimen(P->depth) << ")x" << ruledimen(P->width);
					break;
				}
				case ins_node:
				{
					auto P = dynamic_cast<InsNode*>(p);
					oss << esc("insert") << P->subtype << ", natural size " << asScaled(P->height) << "; split("
						<< asSpec(P->split_top_ptr) << "," << asScaled(P->depth) << "); float cost " << P->float_cost
						<< shownodelist(P->ins_ptr, symbol+".");
					break;
				}
				case whatsit_node:
					switch (dynamic_cast<WhatsitNode*>(p)->subtype)
					{
						case open_node:
						{
							auto P = dynamic_cast<OpenWriteWhatsitNode*>(p);
							oss << writewhatsit("openout", P) << "=" << asFilename(P->open_name, P->open_area, P->open_ext);
							break;
						}
						case write_node:
						{
							auto P = dynamic_cast<NotOpenWriteWhatsitNode*>(p);
							oss << writewhatsit("write", P) << asMark(P->write_tokens);
							break;
						}
						case close_node: 
							oss << writewhatsit("closeout", dynamic_cast<WriteWhatsitNode*>(p));
							break;
						case special_node:
						{
							auto P = dynamic_cast<NotOpenWriteWhatsitNode*>(p);
							oss << esc("special") << asMark(P->write_tokens);
							break;
						}
						case language_node:
						{
							auto P = dynamic_cast<LanguageWhatsitNode*>(p);
							oss << esc("setlanguage") << P->what_lang << " (hyphenmin" << P->what_lhm << "," << P->what_rhm << ")";
							break;
						}
						default: 
							oss << "whatsit?";
					}
					break;
				case glue_node:
				{
					auto pp = dynamic_cast<GlueNode*>(p);
					if (pp->subtype >= a_leaders)
						oss << esc(pp->subtype == c_leaders ? "cleaders" : pp->subtype == x_leaders ? "xleaders" : "leaders ") 
							<< asSpec(pp->glue_ptr) << shownodelist(pp->leader_ptr, symbol+".");
					else
					{
						oss << esc("glue");
						int n = pp->subtype-1;
						auto &glueNames = primName[assign_glue];
						auto &muGlueNames = primName[assign_mu_glue];
						switch (n+1)
						{
							case normal:
								oss << esc("glue") << " " << asSpec(pp->glue_ptr);
								break;
							case cond_math_glue:
								oss << esc("glue") << "(" << esc("nonscript") << ")";
								break;
							case mu_glue:
								oss << esc("glue") << "(" << esc("mskip") << ") " << asSpec(pp->glue_ptr, "mu");
								break;
							default:
								if (glueNames.find(n) != glueNames.end())
								{
									oss << esc("glue") << "(" << esc(glueNames[n]) << ") " << asSpec(pp->glue_ptr);
									break;
								}
								if (muGlueNames.find(n) != muGlueNames.end())
								{
									oss << esc("glue") << "(" << esc(muGlueNames[n]) << ") " << asSpec(pp->glue_ptr);
									break;
								}
								oss << esc("glue") << "(" << "[unknown glue parameter!]" << ") " << asSpec(pp->glue_ptr);
						}
					}
					break;
				}
				case kern_node:
				{
					auto P = dynamic_cast<KernNode*>(p);
					switch(P->subtype)
					{
						case normal:
							oss << esc("kern") << asScaled(P->width);
							break;
						case mu_glue:
							oss << esc("mkern") << asScaled(P->width) << "mu";
							break;
						case acc_kern:
							oss << esc("kern") << " " << asScaled(P->width) << " (for accent)";
							break;
						default:
							oss << esc("kern") << " " << asScaled(P->width);
					}
					break;
				}
				case math_node:
				{
					auto P = dynamic_cast<MathNode*>(p);
					oss << esc("math") << (P->subtype == before ? "on" : "off");
					if (P->width)
						oss << ", surrounded " << asScaled(P->width);
					break;
				}
				case ligature_node:
				{
					auto P = dynamic_cast<LigatureNode*>(p);
					oss << fontandchar(&P->lig_char) << " (ligature ";
					if (P->subtype > 1)
						oss << "|";
					fontinshortdisplay = P->lig_char.font;
					oss << shortdisplay(&P->lig_char);
					if (P->subtype%2)
						oss << "|";
					oss << ")";
					break;
				}
				case penalty_node:
					oss << esc("penalty ") << dynamic_cast<PenaltyNode*>(p)->penalty;
					break;
				case disc_node:
				{
					auto d = dynamic_cast<DiscNode*>(p);
					oss << esc("discretionary");
					if (d->replace_count > 0)
						oss << " replacing " << d->replace_count;
					oss << shownodelist(d->pre_break, symbol+".");
					oss << shownodelist(d->post_break, symbol+"|");
					break;
				}
				case mark_node:
				{
					oss << esc("mark") << asMark(dynamic_cast<MarkNode*>(p)->mark_ptr);
					break;
				}
				case adjust_node:
				{
					oss << esc("vadjust") << shownodelist(dynamic_cast<AdjustNode*>(p)->adjust_ptr, symbol+".");
					break;
				}
				case style_node:
				{
					auto P = dynamic_cast<StyleNode*>(p);
					if (primName[math_style].find(P->subtype) != primName[math_style].end())
						oss << esc(primName[math_style][P->subtype]);
					else
						oss << "Unknown style!";
					break;
				}
				case choice_node:
				{
					auto P = dynamic_cast<ChoiceNode*>(p);
					oss << esc("mathchoice");
					oss << shownodelist(P->display_mlist, symbol+"D");
					oss << shownodelist(P->text_mlist, symbol+"T");
					oss << shownodelist(P->script_mlist, symbol+"S");
					oss << shownodelist(P->script_script_mlist, symbol+"s");
					break;
				}
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
				{
					switch (p->type)
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
							oss << esc("radical") << asDelimiter(dynamic_cast<RadicalNoad*>(p)->left_delimiter);
							break;
						case accent_noad:
							oss << esc("accent") << famandchar(dynamic_cast<AccentNoad*>(p)->accent_chr);
							break;
						case left_noad:
							oss << esc("left") << asDelimiter(dynamic_cast<LeftRightNoad*>(p)->delimiter);
							break;
						case right_noad:
							oss << esc("right") << asDelimiter(dynamic_cast<LeftRightNoad*>(p)->delimiter);
					}
					auto P = dynamic_cast<Noad*>(p);
					if (P->subtype)
						if (P->subtype == limits)
							oss << esc("limits");
						else
							oss << esc("nolimits");
					if (p->type < left_noad)
						oss << subsidiarydata(P->nucleus, '.', symbol);
					oss << subsidiarydata(P->supscr, '^', symbol);
					oss << subsidiarydata(P->subscr, '_', symbol);
					break;
				}
				case fraction_noad:
				{
					auto P = dynamic_cast<FractionNoad*>(p);
					oss << esc("fraction, thickness ") << (P->thickness == default_code ? "= default": asScaled(P->thickness));
					if (P->left_delimiter.small_fam || P->left_delimiter.small_char || P->left_delimiter.large_fam || P->left_delimiter.large_char)
						oss << ", left-delimiter " << asDelimiter(P->left_delimiter);
					if (P->right_delimiter.small_fam || P->right_delimiter.small_char || P->right_delimiter.large_fam || P->right_delimiter.large_char)
						oss << ", right-delimiter " << asDelimiter(P->right_delimiter);
					oss << subsidiarydata(P->numerator, '\\', symbol);
					oss << subsidiarydata(P->denominator, '/', symbol);
					break;
				}
				default: 
					oss << "Unknown node type!";
			}
		next(p);
	}
	return oss.str();
}

std::string showbox(BoxNode *p)
{  
	depththreshold = show_box_depth();
	breadthmax = show_box_breadth();
	if (breadthmax <= 0)
		breadthmax = 5;
	return shownodelist(p, "")+"\n";
}

std::string showcontext(void)
{
	inputstack.back() = curinput; 
	int nn = -1;
	bool bottomline = false;
	std::ostringstream oss;
	for (baseptr = inputstack.size()-1; !bottomline; baseptr--) 
	{
		curinput = inputstack[baseptr];
		if (state)
			if (txt(name) > 17 || baseptr == 0)
				bottomline = true;
		if (baseptr == inputstack.size()-1 || bottomline || nn < error_context_lines())
		{
			if (baseptr == inputstack.size()-1 || state != token_list || token_type != backed_up || loc)
			{
				int l = oss.str().size();
				if (state)
				{
					if (txt(name) <= 17)
						if (terminal_input(name))
							oss << (baseptr == 0 ? "\r<*> " : "\r<insert>  ");
						else
							oss << "\r<read " << (txt(name) == 17 ? "*" : std::to_string((txt(name)-1)))+"> ";
					else
						oss << "\rl."+std::to_string(line) << " ";
					l = oss.str().size()-l;
					tally = 0;
					trickcount = 1000000;
					int j = limit+(buffer[limit] == end_line_char() ? 0 : 1);
					if (j > 0)
						for (int i = start; i < j; i++)
						{
							if (i == loc)
							{
								firstcount = tally; 
								trickcount = std::max(firstcount+1+errorline-halferrorline, errorline);
							}
							if (tally < trickcount)
								trickbuf[tally%errorline] = buffer[i];
							tally++;
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
							oss << (loc == 0 ? "\r<recently read> ": "\r<to be read again> ");
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
					l = oss.str().size()-l;
					tally = 0;
					trickcount = 1000000;
					for (auto c: tokenlist(dynamic_cast<TokenNode*>(token_type < macro ? Start : Start->link), Loc, 100000))
						if (tally < trickcount)
							trickbuf[tally%errorline] = c;
						tally++;
				}
				if (trickcount == 1000000)
				{
					firstcount = tally; 
					trickcount = std::max(tally+1+errorline-halferrorline, errorline);
				}
				int m = tally < trickcount ? tally-firstcount : trickcount-firstcount;
				int p, n;
				if (l+firstcount <= halferrorline)
				{
					p = 0;
					n = l+firstcount;
				}
				else
				{
					oss << "...";
					p = l+firstcount-halferrorline+3;
					n = halferrorline;
				}
				for (int q = p; q < firstcount; q++)
					oss << trickbuf[q%errorline];
				oss << "\n" << std::string(n, ' ');
				p = firstcount+(m + n <= errorline ? m : errorline-n-3);
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
	}
	curinput = inputstack.back();
	return oss.str();
}

//! Do some tracing.
void diagnostic(const std::string &s)
{
	oldsetting = selector;
	if (tracing_online() <= 0 && selector == term_and_log)
	{
		selector = log_only;
		if (history == spotless)
			history = warning_issued;
	}
	print(s);
	selector = oldsetting;
}

void showcurcmdchr(Token t)
{
	diagnostic("\r{"+(mode != shownmode ? asMode(mode)+": " : "")+cmdchr(t)+"}");
	shownmode = mode;
}

static std::string plus(int i, const std::string &s)
{
	if (pagesofar[i])
		return " plus "+asScaled(pagesofar[i])+s;
	return "";
}

static std::string showactivities(void)
{
	std::ostringstream oss;
	nest.back() = curlist;
	oss << "\r\n";
	for (int p = nest.size()-1; p >= 0; p--)
	{
		int m = nest[p].modefield;
		memoryword a = nest[p].auxfield;
		oss << "\r### " << asMode(m) << " entered at line " << abs(nest[p].mlfield);
		if (m == hmode && nest[p].pgfield != (2<<22)+(3<<16)+0) // language=0, hyphenmin=2,3
			oss << " (language" << nest[p].pgfield%(1<<16)  << ":hyphenmin" << (nest[p].pgfield>>22) << "," << ((nest[p].pgfield>>16)%(1<<6)) << ")";
		if (nest[p].mlfield < 0)
			oss << " (\\output routine)";
		if (p == 0)
		{
			if (page_head != pagetail)
			{
				oss << "\r### current page:";
				if (outputactive)
					oss << " (held over for link output)";
				oss << showbox(dynamic_cast<BoxNode*>(page_head->link));
				if (pagecontents > 0)
				{
					oss << "\rtotal height " << asScaled(page_total) << plus(2, "") << plus(3, "fil") << plus(4, "fill") << plus(5, "filll") << (page_shrink ? " minus "+asScaled(page_shrink) : "");
					oss << "\r goal height" << asScaled(page_goal);
					auto r = page_ins_head->link;
					while (r != page_ins_head)
					{
						auto R = dynamic_cast<PageInsNode*>(r);
						oss << "\n" << esc("insert") << R->subtype << " adds " << asScaled(count(R->subtype) == 1000 ? R->height : xovern(R->height, 1000)*count(R->subtype));
						if (r->type == vlist_node)
						{
							auto q = page_head;
							int t = 0;
							do
							{
								next(q);
								if (q->type == ins_node && dynamic_cast<InsNode*>(q)->subtype == R->subtype)
									t++;
							} while (q != R->broken_ins);
							oss << ", #"+std::to_string(t)+" might split";
						}
						next(r);
					}
				}
			}
			if (contrib_head->link)
				oss << "\r### recent contributions:";
		}
		oss <<showbox(dynamic_cast<BoxNode*>(nest[p].headfield->link));
		switch (abs(m))
		{
			//case 0:
			case vmode:
				oss << "\rprevdepth " << (a.int_ <= ignore_depth ? "ignored" : asScaled(a.int_));
				if (nest[p].pgfield)
					oss << ", prevgraf " << nest[p].pgfield << " line" << (nest[p].pgfield == 1 ?"" : "s");
				break;
			case hmode:
				oss << "\rspacefactor " << a.hh.lh;
				if (m > 0 && a.hh.rh > 0)
					oss << ", current language " << a.hh.rh;
				break;
			case mmode:
				if (a.int_)
					oss << "this will be denominator of:" << showbox(box(a.int_));
		}
	}
	oss << "\n";
	return oss.str();
}

void showwhatever(Token t)
{
	int val;
	switch (t.chr)
	{
		case show_lists:
			diagnostic(showactivities());
			print_err("OK");
			if (selector == term_and_log && tracing_online() <= 0)
				selector = term_only;
			print(" (see the transcript file)");
			selector = term_and_log;
			break;
		case show_box_code:
			val = scaneightbitint();
			diagnostic("\r> \\box"+std::to_string(val)+"="+(box(val) == nullptr ? "void" : showbox(box(val)))+"\n");
			print_err("OK");
			if (selector == term_and_log && tracing_online() <= 0)
				selector = term_only;
			print(" (see the transcript file)");
			selector = term_and_log;
			break;
		case show_code:
			t = gettoken();
			printnl("> "+(t.cs ? scs(t.cs)+"=" : "")+meaning(t));
			break;
		default:
			thetoks();
			printnl("> "+tokenshow(dynamic_cast<TokenNode*>(temp_head)));
			flushnodelist(temp_head->link);
			break;
	}
	if (interaction < error_stop_mode)
	{
		error("", "");
		errorcount--;
	}
	else 
		if (tracing_online() > 0)
			error("", "This isn't an error message; I'm just \\showing something.\nType `I\\show...' to show more (e.g., \\show\\cs,\n\\showthe\\count10, \\showbox255, \\showlists).");
		else
			error("", "This isn't an error message; I'm just \\showing something.\nType `I\\show...' to show more (e.g., \\show\\cs,\n\\showthe\\count10, \\showbox255, \\showlists).\nAnd type `I\\tracingonline=1\\show...' to show boxes and\nlists on your terminal as well as in the transcript file.");
}
