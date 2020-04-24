#include "error.h"
#include "printchar.h"
#include "print.h"
#include "println.h"
#include "printnl.h"
#include "slowprint.h"
#include "printesc.h"
#include "printint.h"
#include "jumpout.h"
#include "giveerrhelp.h"
#include "showcontext.h"
#include "clearforerrorprompt.h"
#include "terminput.h"
#include "gettoken.h"
#include "beginfilereading.h"
#include <iostream>

void error(void)
{
	if (history < 2)
		history = 2;
	printchar('.');
	showcontext();
	if (interaction == 3)
		while (true)
		{
			clearforerrorprompt();
			print(264); //? 
			terminput();
			if (last == First)
				return;
			ASCIIcode c = buffer[First];
		  	if (c >= 'a') // minuscule
				c -= 'a'-'A'; // conversion en majuscule
			switch (c)
			{
				case 48:
				case 49:
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
				case 57:
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
						helpline[1] = 279; //I have just deleted some text, as you asked.
						helpline[0] = 280; //You can now delete more, or insert, or whatever.
						showcontext();
						return;
					}
					break;
				case 69: 
					if (baseptr > 0)
					{
						printnl(265); //You want to edit file 
						slowprint(inputstack[baseptr].namefield);
						print(266); // at line 
						printint(line);
						interaction = 2;
						jumpout();
					}
					break;
				case 72:
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
							helpline[1] = 281; //Sorry, I don't know how to help in this situation.
							helpline[0] = 282; //Maybe you should try asking a human?
						}
						do
						{
							helpptr--;
							print(helpline[helpptr]);
							println();
						} while (helpptr);
					}
					helpptr = 4;
					helpline[3] = 283; //Sorry, I already gave what help I could...
					helpline[2] = 282; //Maybe you should try asking a human?
					helpline[1] = 284; //An error might have occurred before I noticed any problems.
					helpline[0] = 285; //``If all else fails, read the instructions.''
					continue;
				case 73:
					beginfilereading();
					if (last > First + 1)
					{
						curinput.locfield = First+1;
						buffer[First] = ' ';
					}
					else
					{
						print(278); //insert>
						terminput();
						curinput.locfield = First;
					}
					First = last;
					curinput.limitfield = last - 1;
					return;
				case 81:
				case 82:
				case 83:
					errorcount = 0;
					interaction = c-81;
					print(273); //OK, entering 
					switch (c)
					{
						case 81:
							printesc(274); //batchmode
							selector--;
						  	break;
						case 82: 
							printesc(275); //nonstopmode
							break;
						case 83:
							printesc(276); //scrollmode
					}
					print(277); // ...
					println();
					std::cout << std::flush;
					return;
				case 88:
					interaction = 2;
					jumpout();
					break;
			}
			print(267); //Type <return> to proceed, S to scroll future error messages,
			printnl(268); //R to run without stopping, Q to run quietly,
			printnl(269); //I to insert something, 
			if (baseptr > 0)
				print(270); //E to edit your file,
			if (deletionsallowed)
				printnl(271); //1 or ... or 9 to ignore the next 1 to 9 tokens of input,
			printnl(272); //H for help, X to quit.
		}
	errorcount++;
	if (errorcount == 100)
	{
		printnl(263); //(That makes 100 errors; please try again.)
		history = 3;
		jumpout();
	}
	if (interaction > 0)
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
	if (interaction > 0)
		selector++;
	println();
}
