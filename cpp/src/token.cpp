#include "token.h"
#include "getnext.h"
#include "lecture.h"
#include "erreur.h"
#include "alignement.h"
#include "expand.h"
#include "impression.h"
#include <sstream>

void strtoks(const std::string &s)
{
	for (auto c: s)
		tempHead.list.push_back(c == ' ' ? space_token : other_token+c);
}

static void scantoks(const char status, bool xpand, Token tk)
{
	warningindex = tk.cs;
	defRef.token_ref_count = 0;
	defRef.list.clear();
	halfword hashbrace = 0;
	halfword t = zero_token;
	halfword unbalance = 0;
	if (status == absorbing)
		scanner.leftBrace(status);
	else
		while (true)
		{
			tk = scanner.get(defining);
			if (tk.tok < right_brace_limit)
			{
				defRef.list.push_back(end_match_token);
				if (tk.cmd == right_brace)
				{
					error("Missing { inserted", "Where was the left brace? You said something like `\\def\\a}',\nwhich I'm going to interpret as `\\def\\a{}'.");
					alignstate++;
					unbalance = 1;
				}
				break;
			}
			if (tk.cmd == mac_param)
			{
				auto s = match_token+tk.chr;
				tk = scanner.get(defining);
				if (tk.cmd == left_brace)
				{
					hashbrace = tk.tok;
					defRef.list.push_back(tk.tok);
					defRef.list.push_back(end_match_token);
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
			defRef.list.push_back(tk.tok);
		}
	while (unbalance)
	{
		if (xpand)
		{
			for (tk = scanner.next(status); tk.cmd > max_command; tk = scanner.next(status))
			{
				if (tk.cmd != the)
					expand(status, tk);
				else
				{
					TokenList tempHead;
					thetoks(status, tempHead);
					if (tempHead.list.size())
						defRef.list.insert(defRef.list.end(), tempHead.list.begin(), tempHead.list.end());
				}
			}
			tk = scanner.xpand(status, tk);
		}
		else
			tk = scanner.get(status);
		switch (tk.cmd)
		{
			case left_brace:
				unbalance++;
				break;
			case right_brace:
				unbalance--;
				break;
			case mac_param:
				if (status == defining)
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

void scanMacroToks(char &status, bool xpand, Token tk) { scantoks(defining, xpand, tk); status = normal; }
void scanNonMacroToks(char &status, Token tk) { scantoks(absorbing, false, tk); status = normal; }
void scanNonMacroToksExpand(char &status, Token tk) { scantoks(absorbing, true, tk); status = normal; }

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

