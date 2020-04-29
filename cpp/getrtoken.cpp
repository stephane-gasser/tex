#include "getrtoken.h"
#include "gettoken.h"
#include "printnl.h"
#include "print.h"
#include "backinput.h"
#include "inserror.h"

void getrtoken(void)
{
	while (true)
	{
		do
			gettoken();
		while (curtok == 2592);
		if (curcs == 0 || curcs > 2614)
		{
			if (interaction == 3)
				printnl(262); //
			print(1183); //Missing control sequence inserted
			helpptr = 5;
			helpline[4] = 1184; //Please don't say `\def cs{...}', say `\def\cs{...}'.
			helpline[3] = 1185; //I've inserted an inaccessible control sequence so that your
			helpline[2] = 1186; //definition will be completed without mixing me up too badly.
			helpline[1] = 1187; //You can recover graciously from this error, if you're
			helpline[0] = 1188; //careful; see exercise 27.2 in The TeXbook.
			if (curcs == 0)
			backinput();
			curtok = 6709;
			inserror();
			continue;
		}
		break;
	}
}
