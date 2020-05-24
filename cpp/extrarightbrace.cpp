#include "extrarightbrace.h"
#include "printnl.h"
#include "print.h"
#include "printchar.h"
#include "error.h"
#include "printesc.h"
#include "texte.h"

void extrarightbrace(void)
{
	printnl("! ");
	print("Extra }, or forgotten ");
	switch (curgroup)
	{
		case 14: 
			printesc("endgroup");
			break;
		case 15: 
			printchar('$');
			break;
		case 16: 
			printesc("right");
	}
	helpptr = 5;
	helpline[4] = txt("I've deleted a group-closing symbol because it seems to be");
	helpline[3] = txt("spurious, as in `$x}$'. But perhaps the } is legitimate and");
	helpline[2] = txt("you forgot something else, as in `\\hbox{$x}'. In such cases");
	helpline[1] = txt("the way to recover is to insert both the forgotten and the");
	helpline[0] = txt("deleted material, e.g., by typing `I$}'.");
	error();
	alignstate++;
}

