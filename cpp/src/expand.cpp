#include "expand.h"
#include "lecture.h"
#include "backinput.h"
#include "getavail.h"
#include "impression.h"
#include "erreur.h"
#include "idlookup.h"
#include "flushlist.h"
#include "eqdefine.h"
#include "conditional.h"
#include "insertrelax.h"
#include "passtext.h"
#include "noeud.h"
#include "startinput.h"
#include "macrocall.h"
#include "texte.h"

void expand(eightbits cmd, halfword chr, halfword cs)
{
	smallnumber radixbackup = radix;
	smallnumber cobackup = curorder;
	halfword backupbackup = link(backup_head);
	if (cmd < call)
	{
		if (tracing_commands() > 1)
			showcurcmdchr(cmd, chr);
		halfword t;
		smallnumber savescannerstatus;
		halfword p, q, r;
		int j;
		halfword tok;
		switch (cmd)
		{
			case top_bot_mark:
				if (curmark[chr])
					begintokenlist(curmark[chr], mark_text);
				break;
			case expand_after:
				std::tie(cmd, chr, tok, cs) = gettoken();
				t = tok;
				std::tie(cmd, chr, tok, cs) = gettoken();
				if (cmd > max_command)
					expand(cmd, chr, cs);
				else
					backinput(tok);
				tok = t;
				backinput(tok);
				break;
			case no_expand:
				savescannerstatus = scannerstatus;
				scannerstatus = 0;
				std::tie(cmd, chr, tok, cs) = gettoken();
				scannerstatus = savescannerstatus;
				t = tok;
				backinput(tok);
				if (t >= cs_token_flag)
				{
					p = getavail();
					info(p) = frozen_dont_expand+cs_token_flag;
					link(p) = loc;
					start = p;
					loc = p;
				}
				break;
			case cs_name:
				r = getavail();
				p = r;
				do
				{
					std::tie(cmd, chr, tok, cs) = getxtoken();
					if (cs == 0)
					{
						q = getavail();
						link(p) = q;
						info(q) = tok;
						p = q;
					}
				} while (cs == 0);
				if (cmd != end_cs_name)
					backerror(tok, "Missing "+esc("endcsname")+" inserted", "The control sequence marked <to be read again> should\nnot appear between \\csname and \\endcsname.");
				j = First;
				p = link(r);
				while (p)
				{
					if (j >= maxbufstack)
					{
						maxbufstack = j+1;
						if (maxbufstack == bufsize)
							overflow("buffer size", bufsize);
					};
					buffer[j++] = info(p)%0x1'00;
					p = link(p);
				};
				if (j > First+1)
				{
					nonewcontrolsequence = false;
					std::string s;
					for (int i = First; i <= j; i++)
						s += buffer[i];
					cs = idlookup(s);
					nonewcontrolsequence = true;
				}
				else 
					if (j == First)
					cs = 513;
				else
					cs = 257+buffer[First];
				flushlist(r);
				if (eq_type(cs) == undefined_cs)
					eqdefine(cs, 0, 256);
				tok = cs+cs_token_flag;
				backinput(tok);
				break;
			case convert: 
				convtoks(chr);
				break;
			case the: 
				insthetoks();
				break;
			case if_test: 
				conditional(chr);
				break;
			case fi_or_else:
				if (chr > iflimit)
					if (iflimit = 1)
						insertrelax(cs);
					else
						error("Extra "+cmdchr(fi_or_else, chr), "I'm ignoring this; it doesn't match any \\if.");
				else
				{
					while (chr != 2)
						passtext();
					p = condptr;
					ifline = if_line_field(p);
					curif = subtype(p);
					iflimit = type(p);
					condptr = link(p);
					freenode(p, 2);
				}
				break;
			case input:
				if (chr > 0)
					forceeof = true;
				else 
					if (nameinprogress)
						insertrelax(cs);
					else
						startinput();
				break;
			default:
				error("Undefined control sequence", "The control sequence at the end of the top line\nof your error message was never \\def'ed. If you have\nmisspelled it (e.g., `\\hobx'), type `I' and the correct\nspelling (e.g., `I\\hbox'). Otherwise just continue,\nand I'll forget about whatever was undefined.");
		}
	}
	else 
		if (cmd < end_template)
			macrocall(chr, cs);
		else
			backinput(frozen_endv+cs_token_flag);
	radix = radixbackup;
	curorder = cobackup;
	link(backup_head) = backupbackup;
}
