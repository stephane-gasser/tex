#include "insertdollarsign.h"
#include "backinput.h"
#include "printnl.h"
#include "print.h"
#include "inserror.h"
#include "texte.h"

void insertdollarsign(void)
{
	backinput();
	curtok = 804; //math_shift + '$'
	printnl("! ");
	print("Missing $ inserted");
	helpptr = 2;
	helpline[1] = txt("I've inserted a begin-math/end-math symbol since I think");
	helpline[0] = txt("you left one out. Proceed, with fingers crossed.");
	inserror();
}

