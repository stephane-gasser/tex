#include "erreur.h"
#include "impression.h"
#include "jumpout.h"
#include "terminput.h"
#include "lecture.h"
#include "beginfilereading.h"
#include "texte.h"
#include "backinput.h"
#include "flushnodelist.h"
#include "endfilereading.h"
#include "normalizeselector.h"
#include <iostream>

void error(const std::string &msg, const std::string &hlp, bool deletionsallowed)
{
	if (msg != "")
		print_err(msg);
	helpline = hlp;
	if (history < error_message_issued)
		history = error_message_issued;
	print("."+showcontext());
	if (interaction == error_stop_mode)
		while (true)
		{
			clearforerrorprompt();
			print("? ");
			terminput();
			if (last == First)
				return;
			ASCIIcode c = buffer[First];
		  	if (c >= 'a') // minuscule
				c -= 'a'-'A'; // conversion en majuscule
			switch (c)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if (deletionsallowed)
					{
						int s1 = curtok;
						int s2 = curcmd;
						int s3 = curchr;
						int s4 = alignstate;
						alignstate = 1000000;
						OKtointerrupt = false;
						if (last > First + 1 && buffer[First+1] >= '0' && buffer[First+1] <= '9')
						  c = (c-'0')*10+buffer[First+1]-'0';
						else
							c -= '0';
						while (c > 0)
						{
							gettoken();
							c--;
						}
						curtok = s1;
						curcmd = s2;
						curchr = s3;
						alignstate = s4;
						OKtointerrupt = true;
						helpline = "I have just deleted some text, as you asked.";
						print(showcontext());
						return;
					}
					break;
				case 'E': 
					if (baseptr > 0)
					{
						printnl("You want to edit file ");
						slowprint(inputstack[baseptr].namefield);
						print(" at line "+std::to_string(line));
						interaction = scroll_mode;
						jumpout();
					}
					break;
				case 'H':
					if (useerrhelp)
						print(tokenshow(err_help()));
					else
						print((helpline == "" ? "Sorry, I don't know how to help in this situation.\nMaybe you should try asking a human?" : helpline)+"\n");
					useerrhelp = false;
					helpline = "Sorry, I already gave what help I could...\nMaybe you should try asking a human?\nAn error might have occurred before I noticed any problems.\n``If all else fails, read the instructions.''";
					continue;
				case 'I':
					beginfilereading();
					if (last > First+1)
					{
						loc = First+1;
						buffer[First] = ' ';
					}
					else
					{
						print("insert>");
						terminput();
						loc = First;
					}
					First = last;
					limit = last - 1;
					return;
				case 'Q':
				case 'R':
				case 'S':
					errorcount = 0;
					interaction = c-'Q';
					print("OK, entering ");
					switch (c)
					{
						case 'Q':
							print(esc("batchmode"));
							selector--;
						  	break;
						case 'R': 
							print(esc("nonstopmode"));
							break;
						case 'S':
							print(esc("scrollmode"));
					}
					print(" ...\n");
					std::cout << std::flush;
					return;
				case 'X':
					interaction = scroll_mode;
					jumpout();
					break;
			}
			print("Type <return> to proceed, S to scroll future error messages,");
			printnl("R to run without stopping, Q to run quietly,");
			printnl("I to insert something, ");
			if (baseptr > 0)
				print("E to edit your file,");
			if (deletionsallowed)
				printnl("1 or ... or 9 to ignore the link 1 to 9 tokens of input,");
			printnl("H for help, X to quit.");
		}
	errorcount++;
	if (errorcount == 100)
	{
		printnl("(That makes 100 errors; please try again.)");
		history = fatal_error_stop;
		jumpout();
	}
	if (interaction > batch_mode)
		selector--;
	if (useerrhelp)
		print("\n"+tokenshow(err_help())+"\n");
	else
		if (helpline != "")
		{
			printnl(helpline+"\n");
			helpline = "";
		}
	if (interaction > batch_mode)
		selector++;
	println();
}

void inserror(const std::string &msg, const std::string &hlp, bool deletionsallowed)
{
	OKtointerrupt = false;
	backinput();
	token_type = inserted;
	OKtointerrupt = true;
	error(msg, hlp, deletionsallowed);
}

//! Back up one token and call \a error.
//!The \a back_error routine is used when we want to replace an offending token
//!just before issuing an error message. This routine, like \a back_input,
//!requires that \a cur_tok has been set. We disable interrupts during the
//!call of \a back_input so that the help message won't be lost.
void backerror(const std::string &msg, const std::string &hlp)
{
	OKtointerrupt = false;
	backinput();
	OKtointerrupt = true;
	error(msg, hlp);
}

//! At certain times box 255 is supposed to be void (i.e., |null|),
//! or an insertion box is supposed to be ready to accept a vertical list.
//!  If not, an error message is printed, and the following subroutine
//!  flushes the unwanted contents, reporting them to the user.
void boxerror(eightbits n, const std::string &msg, const std::string &hlp)
{
	error(msg, hlp);
	diagnostic("\rThe following box has been deleted:"+showbox(box(n))+"\n");
	flushnodelist(box(n));
	box(n) = 0;
}

void clearforerrorprompt(void)
{
	while (state != token_list && terminal_input(name) && inputptr > 0 && loc > limit)
		endfilereading();
	println();
	std::cin.clear();
}

void fatal(const std::string &msg, const std::string &hlp)
{
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error(msg, hlp);
	else
		print_err(msg);
	history = fatal_error_stop;
	jumpout();
}

void confusion(const std::string &s)
{
	normalizeselector();
	if (history < error_message_issued)
		fatal("This can't happen ("+s+")", "I'm broken. Please show this to someone who can fix can fix");
	else
		fatal("I can't go on meeting you like this", "One of your faux pas seems to have wounded me deeply...\nin fact, I'm barely conscious. Please fix it and try again.");
}

void overflow(const std::string &s, int n)
{
	normalizeselector();
	fatal("TeX capacity exceeded, sorry ["+s+"="+std::to_string(n)+"]", "If you really absolutely need more capacity,\nyou can ask a wizard to enlarge me.");
}

void fatalerror(const std::string &s)
{
	normalizeselector();
	fatal("Emergency stop", s);
}

//! make sure that the pool hasn't overflowed
void str_room(int n) 
{
  if (poolptr+n > poolsize)
	  overflow("pool size", poolsize-initpoolptr); 
}

void check_full_save_stack(void)
{
	if (saveptr > maxsavestack)
	{
		maxsavestack = saveptr; 
		if (maxsavestack> savesize-6) 
			overflow("save size",savesize);
	}
}

void interror(int n, const std::string &msg, const std::string &hlp) { error(msg+" ("+std::to_string(n)+")", hlp); }
void reportillegalcase(void) { error("You can't use `"+cmdchr(curcmd, curchr)+"' in "+asMode(mode), "Sorry, but I'm not programmed to handle this case;\nI'll just pretend that you didn't ask for it.\nIf you're in the wrong mode, you might be able to\nreturn to the right one by typing `I}' or `I$' or `I\\par'."); }

bool privileged(void)
{
	if (mode > 0)
		return true;
	reportillegalcase();
	return false;
}

