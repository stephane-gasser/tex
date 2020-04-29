#include "deletetokenref.h"
#include "flushlist.h"

void deletetokenref(halfword p)
{
	if (info(p) == 0)
		flushlist(p);
	else
		info(p)--;
}
