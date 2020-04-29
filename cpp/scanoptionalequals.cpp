#include "scanoptionalequals.h"
#include "getxtoken.h"
#include "backinput.h"

void scanoptionalequals(void)
{
	do
		getxtoken();
	while (curcmd == 10);
	if (curtok != 3133)
		backinput();
}
