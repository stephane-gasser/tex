#include "privileged.h"
#include "reportillegalcase.h"

bool privileged(void)
{
	if (curlist.modefield > 0)
		return true;
	reportillegalcase();
	return false;
}
