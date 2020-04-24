#include "showcurcmdchr.h"
#include "begindiagnostic.h"
#include "printnl.h"
#include "printmode.h"
#include "print.h"
#include "printcmdchr.h"
#include "printchar.h"
#include "enddiagnostic.h"

void showcurcmdchr(void)
{
	begindiagnostic();
	printnl('{');
	if (curlist.modefield != shownmode)
	{
		printmode(curlist.modefield);
		print(568); //: 
		shownmode = curlist.modefield;
	}
	printcmdchr(curcmd, curchr);
	printchar('}');
	enddiagnostic(false);
}
