#include "mathradical.h"
#include "lecture.h"
#include "noeud.h"

void mathradical(Token t)
{
	auto n = new RadicalNoad;
	n->subtype = normal;
	n->nucleus.math_type = 0; // = twohalves{0, 0};
	n->subscr.math_type = 0; // = twohalves{0, 0};
	n->supscr.math_type = 0; // = twohalves{0, 0};
	scandelimiter(n->left_delimiter, true, t);
	scanmath(n->nucleus);
	tail_append(n);
}
