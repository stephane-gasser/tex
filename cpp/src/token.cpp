#include "token.h"
#include "getnext.h"
#include "lecture.h"
#include "erreur.h"
#include "alignement.h"
#include "expand.h"
#include "impression.h"
#include "equivalent.h"
#include "primitive.h"
#include <sstream>

static std::map<quarterword, std::string> echap = { {long_call, "long macro"}, {outer_call, "outer macro"},	{long_outer_call, "long \\outer macro"}, {end_template, "outer endtemplate"} };
static std::map<quarterword, std::string> caract =
{
	{left_brace, "begin-group character "}, {right_brace, "end-group character "}, {math_shift, "math shift character "}, {mac_param, "macro parameter character "}, 
	{sup_mark, "superscript character "}, {sub_mark, "subscript character "}, {spacer, "blank space "}, {letter, "the letter "}, {other_char, "the character "}, {tab_mark, "alignment tab character "}
};

std::string Token::cmdchr(void)
{
	if (primName.find(cmd) != primName.end())
	{
		int n = chr;
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
			return chr < skip_base ? "[unknown glue parameter!]" : esc("skip")+std::to_string(chr-skip_base);
		case assign_mu_glue:
			return chr < mu_skip_base ? "[unknown glue parameter!]" : esc("muskip")+std::to_string(chr-mu_skip_base);
		case assign_toks:
			return esc("toks")+std::to_string(chr-toks_base);
		case assign_int: 
			return chr < count_base ? "[unknown integer parameter!]" : esc("count")+std::to_string(chr-count_base);
		case assign_dimen:
			return chr < scaled_base ? "[unknown dimen parameter!]" : esc("dimen")+std::to_string(chr-scaled_base);
		case char_given:
			return esc("char")+hex(chr);
		case math_given:
			return esc("mathchar")+hex(chr); 
		case set_font:
			return "select font "+fonts[chr].name+(fonts[chr].size == fonts[chr].dsize ? "" : " at "+std::to_string(double(fonts[chr].size)/unity)+"pt");
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
			return caract[cmd]+char(chr);
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

static void scantoks(bool xpand, Token tk)
{
	warningindex = tk.cs;
	defRef = TokenList();
	halfword hashbrace = 0;
	halfword t = zero_token;
	for (bool fin = false; !fin; defRef.list.push_back(tk.tok))
	{
		tk = scanner.get(defining);
		switch (tk.cmd)
		{
			case right_brace:
				error("Missing { inserted", "Where was the left brace? You said something like `\\def\\a}',\nwhich I'm going to interpret as `\\def\\a{}'.");
				alignstate++;
				[[fallthrough]];
			case left_brace:
				defRef.list.push_back(end_match_token);
				fin = true;
				break;
			case mac_param:
			{
				auto s = match_token+tk.chr;
				tk = scanner.get(defining);
				if (tk.cmd == left_brace)
				{
					hashbrace = tk.tok;
					defRef.list.push_back(hashbrace);
					defRef.list.push_back(end_match_token);
					fin = true;						
					break;
				}
				if (t == zero_token+9)
					error("You already have nine parameters", "I'm going to ignore the # sign you just used.");
				else
				{
					t++;
					if (tk.tok != t)
						backerror(tk, "Parameters must be numbered consecutively", "I've inserted the digit you should have used after the #.\nType `1' to delete what you did use.");
					tk.tok = s;
				}
			}
		}
	}
	for (halfword unbalance = 1; unbalance;)
	{
		if (xpand)
		{
			for (tk = scanner.next(defining); tk.cmd > max_command; tk = scanner.next(defining))
				if (tk.cmd == the)
				{
					auto l = thetoks(defining).list;
					defRef.list.insert(defRef.list.end(), l.begin(), l.end());
				}
				else
					expand(defining, tk);
			tk = scanner.xpand(defining, tk);
		}
		else
			tk = scanner.get(defining);
		switch (tk.cmd)
		{
			case left_brace:
				unbalance++;
				break;
			case right_brace:
				unbalance--;
				break;
			case mac_param:
			{
				auto s = tk.tok;
				tk = xpand ? scanner.getX(defining): scanner.get(defining);
				if (tk.cmd != mac_param)
					if (tk.tok <= zero_token || tk.tok > t)
					{
						backerror(tk, "Illegal parameter number in definition of "+scs(warningindex), "You meant to type ## instead of #, right?\nOr maybe a } was forgotten somewhere earlier, and things\nare all screwed up? I'm going to assume that you meant ##.");
						tk.tok = s;
					}
					else
						tk.tok = out_param_token-'0'+tk.chr;
			}
		}
		if (unbalance)
			defRef.list.push_back(tk.tok);
	}
	if (hashbrace)
		defRef.list.push_back(hashbrace);
}

static void scantoks2(bool xpand, Token tk)
{
	warningindex = tk.cs;
	defRef = TokenList();
	scanner.leftBrace(absorbing);
	for (halfword unbalance = 1; unbalance;)
	{
		if (xpand)
		{
			for (tk = scanner.next(absorbing); tk.cmd > max_command; tk = scanner.next(absorbing))
				if (tk.cmd == the)
				{
					auto l = thetoks(absorbing).list;
					defRef.list.insert(defRef.list.end(), l.begin(), l.end());
				}
				else
					expand(absorbing, tk);
			tk = scanner.xpand(absorbing, tk);
		}
		else
			tk = scanner.get(absorbing);
		switch (tk.cmd)
		{
			case left_brace:
				unbalance++;
				break;
			case right_brace:
				unbalance--;
		}
		if (unbalance)
			defRef.list.push_back(tk.tok);
	}
}

void scanMacroToks(bool xpand, Token tk) { scantoks(xpand, tk); }
void scanNonMacroToks(Token tk) { scantoks2(false, tk); }
void scanNonMacroToksExpand(Token tk) { scantoks2(true, tk); }

std::string TokenList::toString(int l)
{
	std::ostringstream oss;
	char matchchr = '#';
	char n = '1';
	for (auto &tk: list)
	{
		if (tk >= cs_token_flag)
			oss << cs(tk-cs_token_flag);
		else
		{
			if (tk < 0)
				oss << esc("BAD.");
			else
				switch (tk>>8)
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
						oss << char(tk%(1<<8));
						break;
					case mac_param:
						oss << std::string(2, tk%(1<<8));
						break;
					case out_param:
						oss << matchchr;
						if (tk%(1<<8) > 9)
							return oss.str()+"!";
						oss << tk%(1<<8);
						break;
					case match:
						matchchr = tk%(1<<8);
						oss << matchchr << n;
						if (++n > '9')
							return oss.str();
						break;
					case end_match: 
						oss << "->";
						break;
					default:
			  			oss << esc("BAD.");
				}
		}
		if (oss.str().size() >= l)
			return oss.str()+esc("ETC.");
	}
	return oss.str();
}

