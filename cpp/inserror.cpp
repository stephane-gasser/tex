#include "inserror.h"
#include "error.h"
#include "backinput.h"

void inserror(void)
{
	OKtointerrupt = false;
	backinput();
	token_type = inserted;
	OKtointerrupt = true;
	error();
}
