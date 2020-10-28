#include "erreur.h"
#include "impression.h"
#include "lecture.h"
#include "noeud.h"
#include "fichier.h"
#include "equivalent.h"
#include "alignement.h"
#include "etat.h"
#include "getnext.h"
#include <iostream>

static std::string helpline;

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
			while (state != token_list && terminal_input(name) && inputstack.size() > 1 && loc > limit)
				endfilereading();
			print("\n? ");
			std::cin.clear();
			terminput();
			if (last == First)
				return;
			switch (buffer[First])
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
						auto c = buffer[First]-'0';
						if (last > First+1 && between('0',buffer[First+1], '9'))
						  c = c*10+buffer[First+1]-'0';
						auto save = alignstate;
						alignstate = 1000000;
						for (; c > 0; c--)
							(void)scanner.get(normal);
						alignstate = save;
						helpline = "I have just deleted some text, as you asked.";
						print(showcontext());
						return;
					}
					break;
				case 'e': 
				case 'E': 
					if (baseptr > 0)
					{
						print("\rYou want to edit file ");
						print(inputstack[baseptr].namefield+" at line "+std::to_string(line));
						interaction = scroll_mode;
						throw std::string("jumpout");
					}
					break;
				case 'h':
				case 'H':
					if (useerrhelp)
						print(tokenshow(err_help()));
					else
						print((helpline == "" ? "Sorry, I don't know how to help in this situation.\nMaybe you should try asking a human?" : helpline)+"\n");
					useerrhelp = false;
					helpline = "Sorry, I already gave what help I could...\nMaybe you should try asking a human?\nAn error might have occurred before I noticed any problems.\n``If all else fails, read the instructions.''";
					continue;
				case 'i':
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
					limit = last-1;
					return;
				case 'q':
				case 'Q':
					errorcount = 0;
					interaction = batch_mode;
					print("OK, entering "+esc("batchmode")+" ...\n");
					selector--;
					std::cout << std::flush;
					return;
				case 'r':
				case 'R':
					errorcount = 0;
					interaction = nonstop_mode;
					print("OK, entering "+esc("nonstopmode")+" ...\n");
					std::cout << std::flush;
					return;
				case 's':
				case 'S':
					errorcount = 0;
					interaction = scroll_mode;
					print("OK, entering "+esc("scrollmode")+" ...\n");
					std::cout << std::flush;
					return;
				case 'X':
					interaction = scroll_mode;
					throw std::string("jumpout");
					break;
			}
			print("Type <return> to proceed, S to scroll future error messages,\rR to run without stopping, Q to run quietly,\rI to insert something, ");
			if (baseptr > 0)
				print("E to edit your file,");
			if (deletionsallowed)
				print("\r1 or ... or 9 to ignore the link 1 to 9 tokens of input,");
			print("\rH for help, X to quit.");
		}
	if (++errorcount == 100)
	{
		print("\r(That makes 100 errors; please try again.)");
		history = fatal_error_stop;
		throw std::string("jumpout");
	}
	if (interaction > batch_mode)
		selector--;
	if (useerrhelp)
		print("\n"+tokenshow(err_help())+"\n");
	else
		if (helpline != "")
		{
			print("\r"+helpline+"\n");
			helpline = "";
		}
	if (interaction > batch_mode)
		selector++;
	println();
}

void inserror(Token t, const std::string &msg, const std::string &hlp, bool deletionsallowed)
{
	backinput(t);
	token_type = inserted;
	error(msg, hlp, deletionsallowed);
}

//! Back up one token and call \a error.
//!The \a back_error routine is used when we want to replace an offending token
//!just before issuing an error message. This routine, like \a back_input,
//!requires that \a cur_tok has been set. We disable interrupts during the
//!call of \a back_input so that the help message won't be lost.
void backerror(Token t, const std::string &msg, const std::string &hlp)
{
	backinput(t);
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
	setBox(n, nullptr);
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
	throw std::string("jumpout");
}

static void normalizeselector(void)
{
	selector = logopened ? term_and_log : term_only;
	if (jobname == "")
		openlogfile();
	if (interaction == batch_mode)
		selector--;
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

void interror(int n, const std::string &msg, const std::string &hlp) { error(msg+" ("+std::to_string(n)+")", hlp); }
void reportillegalcase(Token t) { error("You can't use `"+cmdchr(t)+"' in "+asMode(mode), "Sorry, but I'm not programmed to handle this case;\nI'll just pretend that you didn't ask for it.\nIf you're in the wrong mode, you might be able to\nreturn to the right one by typing `I}' or `I$' or `I\\par'."); }

void charwarning(const Font &ft, eightbits c)
{
	if (tracing_lost_chars() > 0)
		diagnostic("\rMissing character: There is no "+std::string(1, c)+" in font "+ft.name+"!");
}
