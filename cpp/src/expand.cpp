#include "expand.h"
#include "lecture.h"
#include "backinput.h"
#include "impression.h"
#include "erreur.h"
#include "chaine.h"
#include "equivalent.h"
#include "conditional.h"
#include "insertrelax.h"
#include "passtext.h"
#include "noeud.h"
#include "startinput.h"
#include "macrocall.h"
#include "getnext.h"
#include "fichier.h"

void expand(Token tk)
{
	smallnumber radixbackup = radix;
	smallnumber cobackup = curorder;
	auto backupbackup = backup_head->link;
	if (tk.cmd < call)
	{
		if (tracing_commands() > 1)
			showcurcmdchr(tk);
		smallnumber savescannerstatus;
		TokenNode *p, *q, *r;
		int j;
		Token t;
		switch (tk.cmd)
		{
			case top_bot_mark:
				if (curmark[tk.chr])
					begintokenlist(curmark[tk.chr], mark_text);
				break;
			case expand_after:
				tk = gettoken();
				t = tk;
				tk = gettoken();
				if (tk.cmd > max_command)
					expand(tk);
				else
					backinput(tk);
				tk = t;
				backinput(tk);
				break;
			case no_expand:
				savescannerstatus = scannerstatus;
				scannerstatus = normal;
				tk = gettoken();
				scannerstatus = savescannerstatus;
				backinput(tk);
				if (tk.tok >= cs_token_flag)
				{
					p = new TokenNode(frozen_dont_expand+cs_token_flag);
					p->link = Loc;
					Start = p;
					Loc = p;
				}
				break;
			case cs_name:
				r = new TokenNode;
				p = r;
				do
				{
					tk = getxtoken();
					if (tk.cs == 0)
					{
						q = new TokenNode(tk.tok);
						p->link = q;
						p = q;
					}
				} while (tk.cs == 0);
				if (tk.cmd != end_cs_name)
					backerror(tk, "Missing "+esc("endcsname")+" inserted", "The control sequence marked <to be read again> should\nnot appear between \\csname and \\endcsname.");
				j = First;
				for (p = dynamic_cast<TokenNode*>(r->link); p; next(p))
				{
					if (j >= maxbufstack)
					{
						maxbufstack = j+1;
						if (maxbufstack == bufsize)
							overflow("buffer size", bufsize);
					};
					buffer[j++] = p->token%(1<<8);
				}
				if (j > First+1)
					tk.cs = idlookup(std::string(buffer+First, buffer+j+1), false);
				else
					if (j == First)
						tk.cs = null_cs;
					else
						tk.cs = single_base+buffer[First];
				flushnodelist(r);
				if (eqtb_active[tk.cs-active_base].type == undefined_cs)
					eqdefine(&eqtb_active[tk.cs-active_base], relax, 256);
				tk.tok = tk.cs+cs_token_flag;
				backinput(tk);
				break;
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
					auto p = condptr;
					ifline = p->if_line_field;
					curif = p->subtype;
					iflimit = p->type;
					next(condptr);
					delete p;
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
			default:
				error("Undefined control sequence", "The control sequence at the end of the top line\nof your error message was never \\def'ed. If you have\nmisspelled it (e.g., `\\hobx'), type `I' and the correct\nspelling (e.g., `I\\hbox'). Otherwise just continue,\nand I'll forget about whatever was undefined.");
		}
	}
	else 
		if (tk.cmd < end_template)
			macrocall(tk);
		else
		{
			Token t;
			t.tok = frozen_endv+cs_token_flag;
			backinput(t);
		}
	radix = radixbackup;
	curorder = cobackup;
	backup_head->link = backupbackup;
}
