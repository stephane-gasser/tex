#include "cserror.h"
#include "impression.h"
#include "error.h"
#include "texte.h"

void cserror(void)
{
	print_err("Extra "+esc("endcsname"));
	helpptr = 1;
	helpline[0] = "I'm ignoring this, since I wasn't doing a \\csname.";
	error();
}
