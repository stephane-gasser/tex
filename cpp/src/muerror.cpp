#include "muerror.h"
#include "error.h"
#include "impression.h"

void muerror(void)
{
	print_err("Incompatible glue units"); 
	helpptr = 1;
	helpline[0] = "I'm going to assume that 1mu=1pt when they're mixed.";
	error();
}
