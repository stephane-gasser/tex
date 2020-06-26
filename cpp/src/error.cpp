#include "error.h"
#include "impression.h"
#include "jumpout.h"
#include "giveerrhelp.h"
#include "showcontext.h"
#include "clearforerrorprompt.h"
#include "terminput.h"
#include "gettoken.h"
#include "beginfilereading.h"
#include <iostream>
#include "texte.h"

void error(void)
{
	if (history < error_message_issued)
		history = error_message_issued;
	printchar('.');
	showcontext();
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
						showcontext();
						return;
					}
					break;
				case 'E': 
					if (baseptr > 0)
					{
						printnl("You want to edit file ");
						slowprint(inputstack[baseptr].namefield);
						print(" at line ");
						printint(line);
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
							printesc("batchmode");
							selector--;
						  	break;
						case 'R': 
							printesc("nonstopmode");
							break;
						case 'S':
							printesc("scrollmode");
					}
					print(" ...");
					println();
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
