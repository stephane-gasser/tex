#include "youcant.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
#include "printmode.h"

void youcant(void)
{
	printnl("! ");
	print("You can't use `");
	printcmdchr(curcmd, curchr);
	print("' in ");
	printmode(mode);
}
