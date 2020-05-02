#include "scanoptionalequals.h"
#include "getxtoken.h"
#include "backinput.h"

void scanoptionalequals(void)
{
	do
		getxtoken();
	while (curcmd == spacer);
	if (curtok != 3133)
		backinput();
}
