#include "doassignments.h"
#include "lecture.h"
#include "prefixedcommand.h"
#include "getnext.h"
#include "tampon.h"

Token doassignments(char status)
{
	while (true)
	{
		auto t = scanner.getXSkipSpaceAndEscape(status);
		if (t.cmd <= max_non_prefixed_command)
			return t;
		int dummy;
		prefixedcommand(status, t, First, dummy, false);
	}
}
