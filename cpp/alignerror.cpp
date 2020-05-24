#include "alignerror.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "error.h"
#include "backinput.h"
#include "inserror.h"
#include "texte.h"

void alignerror(void)
{
	if (abs(alignstate) > 2)
	{
		printnl("! ");
		print("Misplaced ");
		printcmdchr(curcmd, curchr);
		if (curtok == 1062) // tab_mark + '&'
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
			printnl("! ");
			print("Missing { inserted");
			alignstate++;
			curtok = left_brace*0x01'00+'{'; 
		}
		else
		{
			printnl("! ");
			print("Missing } inserted");
			alignstate--;
			curtok = right_brace*0x01'00+ '}';
		}
		helpptr = 3;
		helpline[2] = "I've put in what seems to be necessary to fix";
		helpline[1] = "the current column of the current alignment.";
		helpline[0] = "Try to go on, since this might almost work.";
		inserror();
	}
}
