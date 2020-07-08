#include "alterboxdimen.h"
#include "lecture.h"

void alterboxdimen(void)
{
	auto c = curchr;
	auto b = scaneightbitint();
	scanoptionalequals();
	int val = scan_normal_dimen();
	if (box(b))
		mem[box(b)+c].int_ = val;
}
