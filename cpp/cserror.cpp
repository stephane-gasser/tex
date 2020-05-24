#include "cserror.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"
#include "texte.h"

void cserror(void)
{
	printnl("! ");
	print("Extra ");
	printesc("endcsname");
	helpptr = 1;
	helpline[0] = txt("I'm ignoring this, since I wasn't doing a \\csname.");
	error();
}
