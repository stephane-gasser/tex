#include "alignerror.h"
#include "impression.h"
#include "error.h"
#include "backinput.h"
#include "inserror.h"
#include "texte.h"

void alignerror(void)
{
	if (abs(alignstate) > 2)
	{
		print_err("Misplaced ");
		printcmdchr(curcmd, curchr);
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
