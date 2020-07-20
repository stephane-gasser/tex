#include "mathradical.h"
#include "lecture.h"
#include "noeud.h"

void mathradical(Token t)
{
	tail_append(getnode(radical_noad_size));
	type(tail) = radical_noad;
	subtype(tail) = normal;
	mem[nucleus(tail)].hh = emptyfield;
	mem[subscr(tail)].hh = emptyfield;
	mem[supscr(tail)].hh = emptyfield;
	scandelimiter(left_delimiter(tail), true, t);
	scanmath(nucleus(tail));
}
