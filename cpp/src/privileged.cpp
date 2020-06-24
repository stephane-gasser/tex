#include "privileged.h"
#include "reportillegalcase.h"

bool privileged(void)
{
	if (mode > 0)
		return true;
	reportillegalcase();
	return false;
}
