#include "expand.h"
#include "lecture.h"
#include "backinput.h"
#include "impression.h"
#include "erreur.h"
#include "chaine.h"
#include "equivalent.h"
#include "conditional.h"
#include "passtext.h"
#include "noeud.h"
#include "startinput.h"
#include "macrocall.h"
#include "getnext.h"
#include "fichier.h"

static void insertrelax(halfword cs)
{
	backinput(cs_token_flag+cs);
	backinput(cs_token_flag+frozen_relax);
	token_type = inserted;
}

void expand(Token tk)
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
			tk = gettoken();
			auto t = tk;
			tk = gettoken();
			if (tk.cmd > max_command)
				expand(tk);
			else
				backinput(tk);
			backinput(t);
			break;
		}
		case no_expand:
		{
			auto savescannerstatus = scannerstatus;
			scannerstatus = normal;
			tk = gettoken();
			scannerstatus = savescannerstatus;
			backinput(tk);
			if (tk.tok >= cs_token_flag)
				Start.list.insert(Start.list.begin()+Loc, frozen_dont_expand+cs_token_flag);
				//Start = Loc;
			break;
		}
		case cs_name:
		{
			TokenList l;
			do
			{
				tk = getxtoken();
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
			convtoks(tk);
			break;
		case the: 
			insthetoks();
			break;
		case if_test: 
			conditional(tk);
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
					startinput();
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
