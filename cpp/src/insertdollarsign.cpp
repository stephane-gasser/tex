#include "insertdollarsign.h"
#include "backinput.h"
#include "impression.h"
#include "inserror.h"
#include "texte.h"

void insertdollarsign(void)
{
	backinput();
	curtok = math_shift_token+'$';
	print_err("Missing $ inserted");
	helpptr = 2;
	helpline[1] = "I've inserted a begin-math/end-math symbol since I think";
	helpline[0] = "you left one out. Proceed, with fingers crossed.";
	inserror();
}

