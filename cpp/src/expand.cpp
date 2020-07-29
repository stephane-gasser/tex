#include "expand.h"
#include "lecture.h"
#include "backinput.h"
#include "impression.h"
#include "erreur.h"
#include "idlookup.h"
#include "eqdefine.h"
#include "conditional.h"
#include "insertrelax.h"
#include "passtext.h"
#include "noeud.h"
#include "startinput.h"
#include "macrocall.h"
#include "texte.h"

void expand(Token tk)
{
	smallnumber radixbackup = radix;
	smallnumber cobackup = curorder;
	halfword backupbackup = link(backup_head);
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
				scannerstatus = 0;
				tk = gettoken();
				scannerstatus = savescannerstatus;
				backinput(tk);
				if (tk.tok >= cs_token_flag)
				{
					p = new TokenNode(frozen_dont_expand+cs_token_flag);
					p->link->num = loc;
					start = p->num;
					loc = p->num;
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
				p = dynamic_cast<TokenNode*>(r->link);
				while (p)
				{
					if (j >= maxbufstack)
					{
						maxbufstack = j+1;
						if (maxbufstack == bufsize)
							overflow("buffer size", bufsize);
					};
					buffer[j++] = p->token%(1<<8);
					p = dynamic_cast<TokenNode*>(p->link);
				}
				if (j > First+1)
				{
					nonewcontrolsequence = false;
					tk.cs = idlookup(std::string(buffer+First, buffer+j+1));
					nonewcontrolsequence = true;
				}
				else 
					if (j == First)
					tk.cs = null_cs;
				else
					tk.cs = single_base+buffer[First];
				flushlist(r->num);
				if (eq_type(tk.cs) == undefined_cs)
					eqdefine(tk.cs, relax, 256);
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
					p->num = condptr;
					ifline = if_line_field(p->num);
					curif = subtype(p->num);
					iflimit = type(p->num);
					condptr = link(p->num);
					delete p;
					freenode(p->num, 2);
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
	link(backup_head) = backupbackup;
}
