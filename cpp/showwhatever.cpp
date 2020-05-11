#include "showwhatever.h"
#include "begindiagnostic.h"
#include "showactivities.h"
#include "enddiagnostic.h"
#include "printnl.h"
#include "scaneightbitint.h"
#include "print.h"
#include "printint.h"
#include "printchar.h"
#include "showbox.h"
#include "gettoken.h"
#include "printmeaning.h"
#include "sprintcs.h"
#include "thetoks.h"
#include "flushlist.h"
#include "tokenshow.h"
#include "error.h"

void showwhatever(void)
{
	halfword p;
	switch (curchr)
	{
		case 3:
			begindiagnostic();
			showactivities();
			enddiagnostic(true);
			printnl(262);//! 
			print(1254); //OK
			if (selector == term_and_log && int_par(tracing_online_code) <= 0)
				selector = term_only;
			print(1255); // (see the transcript file)
			selector = term_and_log;
			break;
		case 1:
			scaneightbitint();
			begindiagnostic();
			printnl(1253); //> \box
			printint(curval);
			printchar('='); //
			if (box(curval) == 0)
				print(410); //void
			else
				showbox(box(curval));
			enddiagnostic(true);
			printnl(262);//! 
			print(1254); //OK
			if (selector == term_and_log && int_par(tracing_online_code) <= 0)
				selector = term_only;
			print(1255); // (see the transcript file)
			selector = term_and_log;
			break;
		case 0:
			gettoken();
			printnl(1247); //> 
			if (curcs)
			{
				sprintcs(curcs);
				printchar('=');
			}
			printmeaning();
			break;
		default:
			p = thetoks();
			printnl(1247); //> 
			tokenshow(temp_head);
			flushlist(link(temp_head));
			break;
	}
	if (interaction < error_stop_mode)
	{
		helpptr = 0;
		errorcount--;
	}
	else 
		if (int_par(tracing_online_code) > 0)
		{
			helpptr = 3;
			helpline[2] = 1242; //This isn't an error message; I'm just \showing something.
			helpline[1] = 1243; //Type `I\show...' to show more (e.g., \show\cs,
			helpline[0] = 1244; //\showthe\count10, \showbox255, \showlists).
		}
		else
		{
		helpptr = 5;
			helpline[4] = 1242; //This isn't an error message; I'm just \showing something.
			helpline[3] = 1243; //Type `I\show...' to show more (e.g., \show\cs,
			helpline[2] = 1244; //\showthe\count10, \showbox255, \showlists).
			helpline[1] = 1245; //And type `I\tracingonline=1\show...' to show boxes and
			helpline[0] = 1246; //lists on your terminal as well as in the transcript file.
		}
	error();
}
