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
		scanleftbrace(status);
	else
		while (true)
		{
			tk = gettoken(defining);
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
				tk = gettoken(defining);
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
			for (tk = getnext(status); tk.cmd > max_command; tk = getnext(status))
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
			tk = xtoken(status, tk);
		}
		else
			tk = gettoken(status);
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
					tk = (xpand ? getxtoken : gettoken)(defining);
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

static int trickcount;
static int firstcount;

std::string tokenlist(TokenList *tl, int l)
{
	std::ostringstream oss;
	ASCIIcode matchchr = '#';
	ASCIIcode n = '0';
	size_t p;
	for (p = 0; p < tl->list.size() && oss.str().size() < l; p++)
	{
		if (p == 0)
		{
			firstcount = oss.str().size();
			trickcount = std::max(firstcount+1+errorline-halferrorline, errorline);
		}
		if (tl->list[p] >= cs_token_flag)
			oss << cs(tl->list[p]-cs_token_flag);
		else
		{
			int m = tl->list[p]>>8;
			int c = tl->list[p]%(1<<8);
			if (tl->list[p] < 0)
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
	}
	if (p < tl->list.size())
		oss << esc("ETC.");
	return oss.str();
}

