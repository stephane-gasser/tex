#include "expand.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "chaine.h"
#include "equivalent.h"
#include "conditional.h"
#include "noeud.h"
#include "macrocall.h"
#include "getnext.h"
#include "fichier.h"
#include "etat.h"

static std::string romanint(int n)
{
	constexpr char s[] = "m2d5c2l5x2v5i";
	int j = 0;
	int v = 1000;
	std::string roman;
	while (true)
	{
		while (n >= v)
		{
			roman += s[j];
			n -= v;
		}
		if (n <= 0)
			return roman;
		int k = j+2;
		int u = v/(s[j+1]-'0');
		if (s[j+1] == '2')
		{
			k += 2;
			u /= s[j+3]-'0';
		}
		if (n+u >= v)
		{
			roman += s[k];
			n += u;
		}
		else
		{
			j += 2;
			v /= s[j-1]-'0';
		}
	}
	return roman;
}

static void convtoks(char status, Token t)
{
	switch (t.chr)
	{
		case number_code:
			strtoks(std::to_string(scanner.getInt(status)));
			break;
		case roman_numeral_code: 
			strtoks(romanint(scanner.getInt(status)));
			break;
		case font_name_code: 
		{
			auto &f = fonts[scanfontident(status)];
			strtoks(f.name+(f.size != f.dsize ? " at "+asScaled(f.size)+"pt" : ""));
			break;
		}
		case string_code:
			strtoks(t.cs ? scs(t.cs) : std::string(1, t.chr));
			break;
		case meaning_code:
			strtoks(meaning(scanner.get(normal)));
			break;
		case job_name_code: 
			if (jobname == "")
				openlogfile();
			strtoks(jobname);
	}
	ins_list(&tempHead);
}

static void insertrelax(halfword cs)
{
	backinput(cs_token_flag+cs);
	backinput(cs_token_flag+frozen_relax);
	token_type = inserted;
}

void expand(char status, Token tk)
{
	smallnumber radixbackup = radix;
	smallnumber cobackup = curorder;
	if (tk.cmd < call)
		if (tracing_commands() > 1)
			showcurcmdchr(tk);
	switch (tk.cmd)
	{
		case top_bot_mark:
			if (curmark[tk.chr])
				beginTokenListAboveMacro(curmark[tk.chr], mark_text);
			break;
		case expand_after:
		{
			tk = scanner.get(status);
			auto t = tk;
			tk = scanner.get(status);
			if (tk.cmd > max_command)
				expand(status, tk);
			else
				backinput(tk);
			backinput(t);
			break;
		}
		case no_expand:
			tk = scanner.get(normal);
			backinput(tk);
			if (tk.tok >= cs_token_flag)
				Start.list.insert(Start.list.begin()+Loc, frozen_dont_expand+cs_token_flag);
				//Start = Loc;
			break;
		case cs_name:
		{
			TokenList l;
			do
			{
				tk = scanner.getX(status);
				if (tk.cs == 0)
					l.list.push_back(tk.tok);
			} while (tk.cs == 0);
			if (tk.cmd != end_cs_name)
				backerror(tk, "Missing "+esc("endcsname")+" inserted", "The control sequence marked <to be read again> should\nnot appear between \\csname and \\endcsname.");
			int j = First;
			for (auto &p: l.list)
			{
				if (j >= maxbufstack)
				{
					maxbufstack = j+1;
					if (maxbufstack == bufsize)
						overflow("buffer size", bufsize);
				};
				buffer[j++] = p%(1<<8);
			}
			if (j > First+1)
				tk.cs = idlookup(std::string(buffer+First, buffer+j+1), false);
			else
				if (j == First)
					tk.cs = null_cs;
				else
					tk.cs = single_base+buffer[First];
			l.list.clear();
			if (eqtb_active[tk.cs-active_base].type == undefined_cs)
				eqtb_active[tk.cs-active_base].define(noPrefix, relax, 256);
			tk.tok = tk.cs+cs_token_flag;
			backinput(tk);
			break;
		}
		case convert: 
			convtoks(status, tk);
			break;
		case the: 
			thetoks(status, tempHead);
			ins_list(&tempHead);
			break;
		case if_test: 
			conditional(status, tk);
			break;
		case fi_or_else:
			if (tk.chr > iflimit)
				if (iflimit == 1)
					insertrelax(tk.cs);
				else
					error("Extra "+cmdchr(tk), "I'm ignoring this; it doesn't match any \\if.");
			else
			{
				while (tk.chr != 2)
					passtext();
				ifline = condptr->if_line_field;
				curif = condptr->subtype;
				iflimit = condptr->type;
				removeNodeAtStart(condptr);
			}
			break;
		case input:
			if (tk.chr > 0)
				forceeof = true;
			else 
				if (nameinprogress)
					insertrelax(tk.cs);
				else
					startinput(status);
			break;
		case call:
		case long_call:
		case outer_call:
		case long_outer_call:
			macrocall(tk);
			break;
		default:
			if (tk.cmd < call)
				error("Undefined control sequence", "The control sequence at the end of the top line\nof your error message was never \\def'ed. If you have\nmisspelled it (e.g., `\\hobx'), type `I' and the correct\nspelling (e.g., `I\\hbox'). Otherwise just continue,\nand I'll forget about whatever was undefined.");
			else
				backinput(frozen_endv+cs_token_flag);
	}
	radix = radixbackup;
	curorder = cobackup;
}
