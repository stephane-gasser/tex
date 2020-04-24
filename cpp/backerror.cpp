#include "backerror.h"
#include "backinput.h"
#include "error.h"

void backerror(void)
{
	OKtointerrupt = false;
	backinput();
	OKtointerrupt = true;
	error();
}
