#include "doassignments.h"
#include "getxtoken.h"
#include "prefixedcommand.h"

void doassignments(void)
{
	while (true)
	{
		do
			getxtoken();
		while (curcmd == 10 || curcmd == 0);
		if (curcmd <= 70)
			return;
		setboxallowed = false;
		prefixedcommand();
		setboxallowed = true;
	}
}
