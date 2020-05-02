#include "doassignments.h"
#include "getxtoken.h"
#include "prefixedcommand.h"

void doassignments(void)
{
	while (true)
	{
		do
			getxtoken();
		while (curcmd == spacer || curcmd == escape);
		if (curcmd <= max_non_prefixed_command)
			return;
		setboxallowed = false;
		prefixedcommand();
		setboxallowed = true;
	}
}
