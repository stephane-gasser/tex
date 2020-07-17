#include "mathradical.h"
#include "lecture.h"
#include "noeud.h"

void mathradical(halfword tok, halfword align)
{
	tail_append(getnode(radical_noad_size));
	type(tail) = radical_noad;
	subtype(tail) = normal;
	mem[nucleus(tail)].hh = emptyfield;
	mem[subscr(tail)].hh = emptyfield;
	mem[supscr(tail)].hh = emptyfield;
	scandelimiter(left_delimiter(tail), true, tok, align);
	scanmath(nucleus(tail), align);
}
