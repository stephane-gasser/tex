#include "muerror.h"
#include "error.h"
#include "printnl.h"
#include "print.h"
#include "texte.h"

void muerror(void)
{
	printnl("! ");
	print("Incompatible glue units"); 
	helpptr = 1;
	helpline[0] = "I'm going to assume that 1mu=1pt when they're mixed.";
	error();
}
