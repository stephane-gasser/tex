#include "mathradical.h"
#include "lecture.h"
#include "noeud.h"

void mathradical(Token t)
{
	auto n = new /*Radical*/Noad;
	n->type = radical_noad;
	n->subtype = normal;
	n->nucleus.math_type = 0; // = twohalves{0, 0};
	n->subscr.math_type = 0; // = twohalves{0, 0};
	n->supscr.math_type = 0; // = twohalves{0, 0};
	tail_append(n);
	scandelimiter(left_delimiter(tail->num), true, t);
	scanmath(nucleus(tail->num));
}
