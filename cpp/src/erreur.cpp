#include "erreur.h"
#include "impression.h"
#include "jumpout.h"
#include "giveerrhelp.h"
#include "terminput.h"
#include "gettoken.h"
#include "beginfilereading.h"
#include "texte.h"
#include "backinput.h"
#include "flushnodelist.h"
#include "endfilereading.h"
#include "normalizeselector.h"
#include <iostream>

void error(void)
{
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
						helpptr = 2;
						helpline[1] = "I have just deleted some text, as you asked.";
						helpline[0] = "You can now delete more, or insert, or whatever.";
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
					{
						giveerrhelp();
						useerrhelp = false;
					}
					else
					{
						if (helpptr == 0)
						{
							helpptr = 2;
							helpline[1] = "Sorry, I don't know how to help in this situation.";
							helpline[0] = "Maybe you should try asking a human?";
						}
						do
						{
							helpptr--;
							print(helpline[helpptr]);
							println();
						} while (helpptr);
					}
					helpptr = 4;
					helpline[3] = "Sorry, I already gave what help I could...";
					helpline[2] = "Maybe you should try asking a human?";
					helpline[1] = "An error might have occurred before I noticed any problems.";
					helpline[0] = "``If all else fails, read the instructions.''";
					continue;
				case 'I':
					beginfilereading();
					if (last > First + 1)
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
	{
		println();
		giveerrhelp();
	}
	else
		while (helpptr > 0)
		{
			helpptr--;
			printnl(helpline[helpptr]);
		}
	println();
	if (interaction > batch_mode)
		selector++;
	println();
}

void inserror(void)
{
	OKtointerrupt = false;
	backinput();
	token_type = inserted;
	OKtointerrupt = true;
	error();
}

void alignerror(void)
{
	if (abs(alignstate) > 2)
	{
		print_err("Misplaced "+cmdchr(curcmd, curchr));
		if (curtok == tab_token+'&')
		{
			helpptr = 6;
			helpline[5] = "I can't figure out why you would want to use a tab mark";
			helpline[4] = "here. If you just want an ampersand, the remedy is";
			helpline[3] = "simple: Just type `I\\&' now. But if some right brace";
			helpline[2] = "up above has ended a previous alignment prematurely,";
			helpline[1] = "you're probably due for more error messages, and you";
			helpline[0] = "might try typing `S' now just to see what is salvageable.";
		}
		else
		{
			helpptr = 5;
			helpline[4] = "I can't figure out why you would want to use a tab mark";
			helpline[3] = "or \\cr or \\span just now. If something like a right brace";
			helpline[2] = "up above has ended a previous alignment prematurely,";
			helpline[1] = "you're probably due for more error messages, and you";
			helpline[0] = "might try typing `S' now just to see what is salvageable.";
		}
		error();
	}
	else
	{
		backinput();
		if (alignstate < 0)
		{
			print_err("Missing { inserted");
			alignstate++;
			curtok = left_brace_token+'{'; 
		}
		else
		{
			print_err("Missing } inserted");
			alignstate--;
			curtok = right_brace_token+ '}';
		}
		helpptr = 3;
		helpline[2] = "I've put in what seems to be necessary to fix";
		helpline[1] = "the current column of the current alignment.";
		helpline[0] = "Try to go on, since this might almost work.";
		inserror();
	}
}

//! Back up one token and call \a error.
//!The \a back_error routine is used when we want to replace an offending token
//!just before issuing an error message. This routine, like \a back_input,
//!requires that \a cur_tok has been set. We disable interrupts during the
//!call of \a back_input so that the help message won't be lost.
void backerror(void)
{
	OKtointerrupt = false;
	backinput();
	OKtointerrupt = true;
	error();
}

void cserror(void)
{
	print_err("Extra "+esc("endcsname"));
	helpptr = 1;
	helpline[0] = "I'm ignoring this, since I wasn't doing a \\csname.";
	error();
}

//! At certain times box 255 is supposed to be void (i.e., |null|),
//! or an insertion box is supposed to be ready to accept a vertical list.
//!  If not, an error message is printed, and the following subroutine
//!  flushes the unwanted contents, reporting them to the user.
void boxerror(eightbits n)
{
	error();
	begindiagnostic();
	printnl("The following box has been deleted:"+showbox(box(n)));
	print(enddiagnostic(true));
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

void fatalerror(const std::string &s)
{
	normalizeselector();
	print_err("Emergency stop");
	helpptr = 1;
	helpline[0] = s;
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}

void interror(int n)
{
	print(" ("+std::to_string(n)+")");
	error();
}

void muerror(void)
{
	print_err("Incompatible glue units"); 
	helpptr = 1;
	helpline[0] = "I'm going to assume that 1mu=1pt when they're mixed.";
	error();
}

void noalignerror(void)
{
	print_err("Misplaced "+esc("noalign"));
	helpptr = 2;
	helpline[1] = "I expect to see \\noalign only after the \\cr of";
	helpline[0] = "an alignment. Proceed, and I'll ignore this case.";
	error();
}

void omiterror(void)
{
	print_err("Misplaced "+esc("omit"));
	helpptr = 2;
	helpline[1] = "I expect to see \\omit only after tab marks or the \\cr of";
	helpline[0] = "an alignment. Proceed, and I'll ignore this case.";
	error();
}

//! make sure that the pool hasn't overflowed
void str_room(int n) 
{
  if (poolptr+n > poolsize)
	  overflow("pool size", poolsize-initpoolptr); 
}

void overflow(const std::string &s, int n)
{
	normalizeselector();
	print_err("TeX capacity exceeded, sorry ["+s+"="+std::to_string(n)+"]");
	helpptr = 2;
	helpline[1] = "If you really absolutely need more capacity,";
	helpline[0] = "you can ask a wizard to enlarge me.";
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
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

void youcant(void)
{
	print_err("You can't use `"+cmdchr(curcmd, curchr)+"' in "+asMode(mode));
}

void reportillegalcase(void)
{
	youcant();
	helpptr = 4;
	helpline[3] = "Sorry, but I'm not programmed to handle this case;";
	helpline[2] = "I'll just pretend that you didn't ask for it.";
	helpline[1] = "If you're in the wrong mode, you might be able to";
	helpline[0] = "return to the right one by typing `I}' or `I$' or `I\\par'.";
	error();
}

void giveerrhelp(void)
{
	print(tokenshow(err_help()));
}

bool privileged(void)
{
	if (mode > 0)
		return true;
	reportillegalcase();
	return false;
}

static void erreurConfusion1(const std::string &s)
{
	print_err("This can't happen ("+s+")");
	helpptr = 1;
	helpline[0] = "I'm broken. Please show this to someone who can fix can fix";
}

static void erreurConfusion2(void)
{
	print_err("I can't go on meeting you like this");
	helpptr = 2;
	helpline[1] = "One of your faux pas seems to have wounded me deeply...";
	helpline[0] = "in fact, I'm barely conscious. Please fix it and try again.";
}

void confusion(const std::string &s)
{
	normalizeselector();
	if (history < error_message_issued)
		erreurConfusion1(s);
	else
		erreurConfusion2();
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
