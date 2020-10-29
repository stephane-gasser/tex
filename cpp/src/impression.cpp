#include "impression.h"
#include "calcul.h"
#include "lecture.h" 
#include "noeud.h"
#include "erreur.h"
#include "primitive.h"
#include "police.h"
#include "equivalent.h"
#include "buildpage.h"
#include "chaine.h"
#include "fichier.h"
#include "getnext.h"
#include <sstream> 
#include <iostream> 
#include <cmath>

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
}

static std::string hex(int t)
{
  std::ostringstream oss;
  oss << "\"" << std::hex << t;
  return oss.str();
}

void print(const std::string &s)
{
	for (auto c: s)
		printchar(c);
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

std::string Delimiter::print(void)
{
	int a = (small_fam<<20)+(small_char<<12)+(large_fam<<8)+large_char;
	return a < 0 ? std::to_string(a) : hex(a);
}

std::string esc(const std::string &s)
{
	auto &c = escape_char();
	if (c >= 0 && c < 256)
		return char(c)+s;
	return s;
}

std::string NoadContent::famandchar(void)
{
	return esc("fam")+std::to_string(fam)+" "+std::string(1, character);
}

std::string asFilename(const std::string &n, const std::string &a, const std::string &e)
{
	return a+n+e;
}

static std::string fontandchar(CharNode *p)
{
	if (p->font == 0)
		return "*"+esc("FONT")+" "+char(p->character);
	return esc(fonts[p->font].name)+esc("FONT")+" "+char(p->character);
}

static std::string glue(scaled d, int order, const std::string &s = "")
{
	if (order < 0 || order > 3)
		return asScaled(d)+"foul";
	if (order > 0)
		return asScaled(d)+"fi"+std::string(order, 'l');
	return s;
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

static std::string asMark(TokenList *p)
{
	return "{"+p->toString(maxprintline-10)+"}";
}

std::string meaning(Token t) { return cmdchr(t)+(t.cmd >= call ? ":\n"+TokenList({t.chr}).toString(10000000) : t.cmd == top_bot_mark ?":\n"+tokenshow(curmark[t.chr]) : ""); }

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

static void printnl(const std::string &s) // remplacé par "\r"
{
	if ((termoffset > 0 && selector%2 == 1) || (fileoffset > 0 && selector >= log_only))
		println();
	print(s);
}

static std::string ruledimen(scaled d)
{
	if (is_running(d))
		return "*";
	return asScaled(d);
}

std::string asScaled(scaled s) { return std::to_string(double(s)/unity); }

std::string GlueSpec::print(const std::string &s)
{
	return asScaled(width)+s+(stretch ? " plus "+glue(stretch, stretch_order, s) : "")+(shrink ? " minus "+glue(shrink, shrink_order, s) : "");
}

static std::string shownodelist(LinkedNode*, const std::string &);

static int depththreshold;

//! Display a noad field.
std::string NoadContent::subsidiarydata(char c, const std::string &symbol)
{
	if (cur_length() >= depththreshold)
	{
		if (math_type)
			return " []";
		return "";
	}
	std::ostringstream oss;
	switch (math_type)
	{
		case math_char:
			oss << "\n" << symbol << c << famandchar();
			break;
		case sub_box: 
			oss << shownodelist(info, symbol+c);
			break;
		case sub_mlist:
			if (info == nullptr)
				oss << "\n" << symbol << c << "{}";
			else
				oss << shownodelist(info, symbol+c);
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

void print_err(const std::string &s) { print("\r! "+s); }

std::string tokenshow(TokenList *p)
{
	return p ? p->toString(10000000) : "";
}

std::string shortdisplay(LinkedNode *p)
{
	std::ostringstream oss;
	for (; p; next(p))
	{
		oss << p->shortDisplay();
		if (p->type == disc_node)
			for (int n = dynamic_cast<DiscNode*>(p)->replace_count; n > 0; n--)
				if (p->link)
					next(p);
	}
	return oss.str();
}

static int breadthmax;

static std::string shownodelist(LinkedNode *p, const std::string &symbol)
{
	if (cur_length() > depththreshold)
	{
		if (p)
			return " []";
		return "";
	}
	int n = 0;
	std::ostringstream oss;
	for (; p; next(p))
	{
		oss << "\n" << symbol;
		n++;
		if (n > breadthmax)
			return oss.str()+"etc.";
		oss << p->showNode(symbol);
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

static bool isFile(void) { return name.size() == 1 && name[0] <= 17; }

std::string showcontext(void)
{
	inputstack.back() = curinput; 
	int nn = -1;
	bool bottomline = false;
	std::ostringstream OSS;
	for (baseptr = inputstack.size()-1; !bottomline; baseptr--) 
	{
		curinput = inputstack[baseptr];
		bottomline = state != token_list && (!isFile() || baseptr == 0);
		if (baseptr != inputstack.size()-1 && bottomline && nn >= error_context_lines())
		{
			if (nn == error_context_lines())
			{
				OSS << "\r...";
				nn++;
			}
		}
		else
		{
			if (baseptr == inputstack.size()-1 || state != token_list || token_type != backed_up || loc)
			{
				std::ostringstream oss;
				std::string trickbuf;
				int trickcount;
				int firstcount;
				int m;
				if (state != token_list)
				{
					if (terminal_input(name))
						oss << (baseptr == 0 ? "\r<*> " : "\r<insert>  ");
					else 
						if (isFile())
							oss << "\r<read " << (name[0] == 17 ? "*" : std::to_string(name[0]-1))+"> ";
						else
							oss << "\rl."+std::to_string(line) << " ";
					int j = buffer[limit] == end_line_char() ? limit-start : limit+1-start;
					firstcount = std::min(loc-start, j);
					trickcount = std::max(firstcount+1+errorline-halferrorline, errorline);
					m = std::min(j, trickcount);
					trickbuf = buffer.substr(start, m);
					m -= firstcount;
				}
				else
				{
					static std::map<int, std::string> text = 
					{
						{parameter, "argument"}, {u_template, "template"}, {v_template, "template"}, 
						{inserted, "inserted text"}, {output_text, "output"}, {every_par_text, "everypar"},
						{every_math_text, "everymath"}, {every_display_text, "everydisplay"}, 
						{every_hbox_text, "everyhbox"}, {every_vbox_text, "everyvbox"},
						{every_job_text, "everyjob"}, {every_cr_text, "everycr"}, {mark_text, "mark"}, 
						{write_text, "write"}
					};
					switch (token_type)
					{
						case backed_up: 
							oss << (Loc == 0 ? "\r<recently read> ": "\r<to be read again> ");
							break;
						case macro:
							oss << "\n" << name;
							break;
						default:
							if (text.find(token_type) == text.end())
								oss << "\r?";
							else
								oss << "\r<"+text[token_type]+"> ";
					}
					trickbuf = Start.toString(100000);
					firstcount = trickbuf.size();
					trickcount = std::max(firstcount+1+errorline-halferrorline, errorline);
					m = 0;
				}
				int p = 0, n = oss.str().size()+firstcount;
				if (n > halferrorline)
				{
					oss << "...";
					p = n-halferrorline+3;
					n = halferrorline;
				}
				oss << trickbuf.substr(p, firstcount-p) << "\n" << std::string(n, ' ');
				if (m+n <= errorline)
					oss << trickbuf.substr(firstcount, m);
				else
					oss << trickbuf.substr(firstcount, errorline-n-3) << "...";
				nn++;
				OSS << oss.str();
			}
		}
	}
	curinput = inputstack.back();
	return OSS.str();
}

//! Do some tracing.
void diagnostic(const std::string &s)
{
	auto oldsetting = selector;
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
	static int shownmode = 0; //-203..203
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

void showwhatever(const char status, Token t)
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
			val = scanner.getUInt8(status);
			diagnostic("\r> \\box"+std::to_string(val)+"="+(box(val) == nullptr ? "void" : showbox(box(val)))+"\n");
			print_err("OK");
			if (selector == term_and_log && tracing_online() <= 0)
				selector = term_only;
			print(" (see the transcript file)");
			selector = term_and_log;
			break;
		case show_code:
			t = scanner.get(status);
			print("\r> "+(t.cs ? scs(t.cs)+"=" : "")+meaning(t));
			break;
		default:
			thetoks(status, tempHead);
			print("\r> "+tokenshow(&tempHead));
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

std::string CharNode::showNode(const std::string &) { return fontandchar(this); }

std::string BoxNode::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc(type == hlist_node ? "hbox" : "vbox");
	oss << "(" << asScaled(height) << "+" << asScaled(depth) << ")x" << asScaled(width);
	auto g = glue_set;
	if (g && glue_sign)
	{
		oss << ", glue set ";
		if (glue_sign == shrinking)
			oss << "- ";
		if (!std::isfinite(glue_set))
			oss << "?.?";
		else 
			if (abs(glue_set) > 20000.0)
			{
				if (glue_set > 0.0)
					oss << ">";
				else
					oss << "< -";
				oss << glue(20000*unity, glue_order);
			}
			else
				oss << glue(round(unity*glue_set), glue_order);
	}
	if (shift_amount)
		oss << ", shifted " << asScaled(shift_amount);
	oss << shownodelist(list_ptr, symbol+".");
	return oss.str();
}

std::string UnsetNode::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc("unsetbox");
	oss << "(" << asScaled(height) << "+" << asScaled(depth) << ")x" << asScaled(width);
	if (span_count)
		oss << " (" << span_count+1 << " columns)";
	if (glue_stretch)
		oss << ", stretch " << glue(glue_stretch, glue_order);
	if (glue_shrink)
		oss << ", shrink " << glue(glue_shrink, glue_sign);
	oss << shownodelist(list_ptr, symbol+".");
	return oss.str();
}

std::string RuleNode::showNode(const std::string &)
{
	std::ostringstream oss;
	oss << esc("rule") << "(" << ruledimen(height) << "+" << ruledimen(depth) << ")x" << ruledimen(width);
	return oss.str();
}

std::string InsNode::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc("insert") << subtype << ", natural size " << asScaled(height) << "; split("
		<< split_top_ptr->print() << "," << asScaled(depth) << "); float cost " << float_cost
		<< shownodelist(ins_ptr, symbol+".");
	return oss.str();
}

std::string WhatsitNode::showNode(const std::string &) { return "whatsit?"; }
std::string WriteWhatsitNode::showNode(const std::string &) { return writewhatsit("closeout", this); }

std::string OpenWriteWhatsitNode::showNode(const std::string &)
{
	std::ostringstream oss;
	oss << writewhatsit("openout", this) << "=" << asFilename(open_name, open_area, open_ext);
	return oss.str();
}

std::string NotOpenWriteWhatsitNode::showNode(const std::string &)
{
	std::ostringstream oss;
	if (subtype == special_node)
		oss << esc("special");
	else
		oss << writewhatsit("write", this);
	oss << asMark(write_tokens);
	return oss.str();
}

std::string LanguageWhatsitNode::showNode(const std::string &)
{
	std::ostringstream oss;
	oss << esc("setlanguage") << what_lang << " (hyphenmin" << what_lhm << "," << what_rhm << ")";
	return oss.str();
}

std::string GlueNode::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	if (subtype >= a_leaders)
		oss << esc(subtype == c_leaders ? "cleaders" : subtype == x_leaders ? "xleaders" : "leaders ") 
			<< glue_ptr->print() << shownodelist(leader_ptr, symbol+".");
	else
	{
		oss << esc("glue");
		auto &glueNames = primName[assign_glue];
		auto &muGlueNames = primName[assign_mu_glue];
		switch (subtype)
		{
			case normal:
				oss << esc("glue") << " " << glue_ptr->print();
				break;
			case cond_math_glue:
				oss << esc("glue") << "(" << esc("nonscript") << ")";
				break;
			case mu_glue:
				oss << esc("glue") << "(" << esc("mskip") << ") " << glue_ptr->print("mu");
				break;
			default:
				int n = subtype-1;
				if (glueNames.find(n) != glueNames.end())
				{
					oss << esc("glue") << "(" << esc(glueNames[n]) << ") " << glue_ptr->print();
					break;
				}
				if (muGlueNames.find(n) != muGlueNames.end())
				{
					oss << esc("glue") << "(" << esc(muGlueNames[n]) << ") " << glue_ptr->print();
					break;
				}
				oss << esc("glue") << "(" << "[unknown glue parameter!]" << ") " << glue_ptr->print();
		}
	}
	return oss.str();
}

std::string KernNode::showNode(const std::string &)
{
	switch(subtype)
	{
		case normal:
			return esc("kern")+asScaled(width);
		case mu_glue:
			return esc("mkern")+asScaled(width)+"mu";
		case acc_kern:
			return esc("kern ")+asScaled(width)+" (for accent)";
		default:
			return esc("kern ")+asScaled(width);
	}
}

std::string MathNode::showNode(const std::string &)
{
	std::ostringstream oss;
	oss << esc("math") << (subtype == before ? "on" : "off");
	if (width)
		oss << ", surrounded " << asScaled(width);
	return oss.str();
}

std::string LigatureNode::showNode(const std::string &)
{
	std::ostringstream oss;
	oss << fontandchar(this) << " (ligature ";
	if (subtype > 1) // implicit left boundary
		oss << "|";
	fontinshortdisplay = font;
	oss << shortDisplay();
	if (subtype%2) // implicit right boundary
		oss << "|";
	oss << ")";
	return oss.str();
}

std::string PenaltyNode::showNode(const std::string &) { return esc("penalty ")+std::to_string(penalty); }

std::string DiscNode::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc("discretionary");
	if (replace_count > 0)
		oss << " replacing " << replace_count;
	oss << shownodelist(pre_break, symbol+".");
	oss << shownodelist(post_break, symbol+"|");
	return oss.str();
}

std::string MarkNode::showNode(const std::string &) { return esc("mark")+asMark(mark_ptr); }
std::string AdjustNode::showNode(const std::string &symbol) { return esc("vadjust")+shownodelist(adjust_ptr, symbol+"."); }

std::string StyleNode::showNode(const std::string &)
{
	if (primName[math_style].find(subtype) != primName[math_style].end())
		return esc(primName[math_style][subtype]);
	return "Unknown style!";
}

std::string ChoiceNode::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc("mathchoice");
	oss << shownodelist(display_mlist, symbol+"D");
	oss << shownodelist(text_mlist, symbol+"T");
	oss << shownodelist(script_mlist, symbol+"S");
	oss << shownodelist(script_script_mlist, symbol+"s");
	return oss.str();
}

std::string FractionNoad::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc("fraction, thickness ") << (thickness == default_code ? "= default": asScaled(thickness));
	if (left_delimiter.small_fam || left_delimiter.small_char || left_delimiter.large_fam || left_delimiter.large_char)
		oss << ", left-delimiter " << left_delimiter.print();
	if (right_delimiter.small_fam || right_delimiter.small_char || right_delimiter.large_fam || right_delimiter.large_char)
		oss << ", right-delimiter " << right_delimiter.print();
	oss << numerator.subsidiarydata('\\', symbol);
	oss << denominator.subsidiarydata('/', symbol);
	return oss.str();
}

std::string Noad::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	switch (type)
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
	}
	switch (subtype)
	{
		case 0:
			break;
		case limits:
			oss << esc("limits");
			break;
		default:
			oss << esc("nolimits");
	}
	oss << nucleus.subsidiarydata( '.', symbol);
	oss << supscr.subsidiarydata('^', symbol);
	oss << subscr.subsidiarydata('_', symbol);
	return oss.str();
}

std::string RadicalNoad::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc("radical") << left_delimiter.print();
	switch (subtype)
	{
		case 0:
			break;
		case limits:
			oss << esc("limits");
			break;
		default:
			oss << esc("nolimits");
	}
	oss << nucleus.subsidiarydata( '.', symbol);
	oss << supscr.subsidiarydata('^', symbol);
	oss << subscr.subsidiarydata('_', symbol);
	return oss.str();
}

std::string AccentNoad::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc("accent") << accent_chr.famandchar();
	switch (subtype)
	{
		case 0:
			break;
		case limits:
			oss << esc("limits");
			break;
		default:
			oss << esc("nolimits");
	}
	oss << nucleus.subsidiarydata( '.', symbol);
	oss << supscr.subsidiarydata('^', symbol);
	oss << subscr.subsidiarydata('_', symbol);
	return oss.str();
}

std::string LeftRightNoad::showNode(const std::string &symbol)
{
	std::ostringstream oss;
	oss << esc(type == left_noad ? "left" : "right") << delimiter.print();
	switch (subtype)
	{
		case 0:
			break;
		case limits:
			oss << esc("limits");
			break;
		default:
			oss << esc("nolimits");
	}
	oss << supscr.subsidiarydata('^', symbol);
	oss << subscr.subsidiarydata('_', symbol);
	return oss.str();
}
