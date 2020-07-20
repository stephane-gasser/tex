#include "doassignments.h"
#include "lecture.h"
#include "prefixedcommand.h"

Token doassignments(void)
{
	while (true)
	{
		Token t;
		do
			t = getxtoken();
		while (t.cmd == spacer || t.cmd == escape);
		if (t.cmd <= max_non_prefixed_command)
			return t;
		setboxallowed = false;
		prefixedcommand(t);
		setboxallowed = true;
	}
}
