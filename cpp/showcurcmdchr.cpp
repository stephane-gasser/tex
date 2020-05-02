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
	if (mode != shownmode)
	{
		printmode(mode);
		print(568); //: 
		shownmode = mode;
	}
	printcmdchr(curcmd, curchr);
	printchar('}');
	enddiagnostic(false);
}
