#include "mathradical.h"
#include "lecture.h"
#include "noeud.h"

void mathradical(Token t)
{
	tail_append(getnode(radical_noad_size));
	type(tail) = radical_noad;
	subtype(tail) = normal;
	mem[nucleus(tail)].hh = twohalves{0, 0};
	mem[subscr(tail)].hh = twohalves{0, 0};
	mem[supscr(tail)].hh = twohalves{0, 0};
	scandelimiter(left_delimiter(tail), true, t);
	scanmath(nucleus(tail));
}
