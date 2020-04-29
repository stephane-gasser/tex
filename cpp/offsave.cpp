#include "offsave.h"
#include "printnl.h"
#include "printcmdchr.h"
#include "print.h"
#include "backinput.h"
#include "error.h"
#include "printesc.h"
#include "getavail.h"
#include "printchar.h"
#include "begintokenlist.h"

void offsave(void)
{
	halfword p;
	if (curgroup == 0)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(776); //Extra 
		printcmdchr(curcmd, curchr);
		helpptr = 1;
		helpline[0] = 1042; //Things are pretty mixed up, but I think the worst is over.
		error();
	}
	else
	{
		backinput();
		p = getavail();
		link(29997) = p;
		if (interaction == 3)
			printnl(262); //! 
		print(625); //Missing 
		switch (curgroup)
		{
			case 14:
				info(p) = 6711;
				printesc(516); //endgroup
				break;
			case 15:
				info(p) = 804;
				printchar('$');
				break;
			case 16:
				info(p) = 6712;
				link(p) = getavail();
				p = link(p);
				info(p) = 3118;
				printesc(1041); //right.
				break;
			default:
				info(p) = 637;
				printchar('}');
		}
		print(626); // inserted
		begintokenlist(link(29997), 4);
		{
			helpptr = 5;
			helpline[4] = 1036; //I've inserted something that you may have forgotten.
			helpline[3] = 1037; //(See the <inserted text> above.)
			helpline[2] = 1038; //With luck, this will get me unwedged. But if you
			helpline[1] = 1039; //really didn't forget anything, try typing `2' now; then
			helpline[0] = 1040; //my insertion and my current dilemma will both disappear.
		}
		error();
	}
}
