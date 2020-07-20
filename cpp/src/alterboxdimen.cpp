#include "alterboxdimen.h"
#include "lecture.h"

void alterboxdimen(Token t)
{
	auto c = t.chr;
	auto b = scaneightbitint();
	scanoptionalequals();
	int val = scan_normal_dimen();
	if (box(b))
		mem[box(b)+c].int_ = val;
}
