#include "alignerror.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "error.h"
#include "backinput.h"
#include "inserror.h"

void alignerror(void)
{
	if (abs(alignstate) > 2)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1113); //Misplaced 
		printcmdchr(curcmd, curchr);
		if (curtok == 1062)
		{
			helpptr = 6;
			helpline[5] = 1114; //I can't figure out why you would want to use a tab mark
			helpline[4] = 1115; //here. If you just want an ampersand, the remedy is
			helpline[3] = 1116; //simple: Just type `I\&' now. But if some right brace
			helpline[2] = 1117; //up above has ended a previous alignment prematurely,
			helpline[1] = 1118; //you're probably due for more error messages, and you
			helpline[0] = 1119; //might try typing `S' now just to see what is salvageable.
		}
		else
		{
			helpptr = 5;
			helpline[4] = 1114; //I can't figure out why you would want to use a tab mark
			helpline[3] = 1120; //or \cr or \span just now. If something like a right brace
			helpline[2] = 1117; //up above has ended a previous alignment prematurely,
			helpline[1] = 1118; //you're probably due for more error messages, and you
			helpline[0] = 1119; //might try typing `S' now just to see what is salvageable.
		}
		error();
	}
	else
	{
		backinput();
		if (alignstate < 0)
		{
			if (interaction == 3)
				printnl(262); //! 
			print(657); //Missing { inserted
			alignstate++;
			curtok = 379;
		}
		else
		{
			if (interaction == 3);
				printnl(262); //! 
			print(1109); //Missing } inserted
			alignstate--;
			curtok = 637;
		}
		helpptr = 3;
		helpline[2] = 1110; //I've put in what seems to be necessary to fix
		helpline[1] = 1111; //the current column of the current alignment.
		helpline[0] = 1112; //Try to go on, since this might almost work.
		inserror();
	}
}
