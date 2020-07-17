#include "doassignments.h"
#include "lecture.h"
#include "prefixedcommand.h"

std::tuple<eightbits, halfword> doassignments(halfword align)
{
	while (true)
	{
		eightbits cmd;
		halfword chr, tok;
		do
			std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
		while (cmd == spacer || cmd == escape);
		if (cmd <= max_non_prefixed_command)
			return std::make_tuple(cmd, tok);
		setboxallowed = false;
		prefixedcommand(cmd, chr, align);
		setboxallowed = true;
	}
}
