#include "doassignments.h"
#include "lecture.h"
#include "prefixedcommand.h"
#include "getnext.h"

Token doassignments(void)
{
	while (true)
	{
		auto t = getXTokenSkipSpaceAndEscape(scannerstatus);
		if (t.cmd <= max_non_prefixed_command)
			return t;
		prefixedcommand(t, false);
	}
}
