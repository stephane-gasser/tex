#include "mathradical.h"
#include "lecture.h"
#include "noeud.h"

void mathradical(Token t)
{
	tail_append(getnode(radical_noad_size));
	tail->type = radical_noad;
	subtype(tail->num) = normal;
	mem[nucleus(tail->num)].hh = twohalves{0, 0};
	mem[subscr(tail->num)].hh = twohalves{0, 0};
	mem[supscr(tail->num)].hh = twohalves{0, 0};
	scandelimiter(left_delimiter(tail->num), true, t);
	scanmath(nucleus(tail->num));
}
