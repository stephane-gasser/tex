#include "youcant.h"
#include "impression.h"

void youcant(void)
{
	print_err("You can't use `");
	printcmdchr(curcmd, curchr);
	print("' in ");
	printmode(mode);
}
