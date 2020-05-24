#include "headforvmode.h"
#include "offsave.h"
#include "printnl.h"
#include "printesc.h"
#include "print.h"
#include "error.h"
#include "backinput.h"
#include "texte.h"

void headforvmode(void)
{
	if (mode < 0)
		if (curcmd != hrule)
			offsave();
		else
		{
			printnl("! ");
			print("You can't use `");
			printesc("hrule");
			print("' here except with leaders");
			helpptr = 2;
			helpline[1] = txt("To put a horizontal rule in an hbox or an alignment,");
			helpline[0] = txt("you should use \\leaders or \\hrulefill (see The TeXbook).");
			error();
		}
	else
	{
		backinput();
		curtok = partoken;
		backinput();
		curinput.indexfield = 4;
	}
}
