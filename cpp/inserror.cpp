#include "inserror.h"
#include "error.h"
#include "backinput.h"

void inserror(void)
{
	OKtointerrupt = false;
	backinput();
	curinput.indexfield = 4;
	OKtointerrupt = true;
	error();
}
