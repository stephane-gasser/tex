#include "alterboxdimen.h"
#include "lecture.h"

void alterboxdimen(halfword chr)
{
	auto c = chr;
	auto b = scaneightbitint();
	scanoptionalequals();
	int val = scan_normal_dimen();
	if (box(b))
		mem[box(b)+c].int_ = val;
}
