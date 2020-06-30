#include "youcant.h"
#include "impression.h"

void youcant(void)
{
	print_err("You can't use `"+cmdchr(curcmd, curchr)+"' in ");
	printmode(mode);
}
