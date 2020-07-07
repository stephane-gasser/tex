#include "alterboxdimen.h"
#include "lecture.h"

void alterboxdimen(void)
{
	auto c = curchr;
	curval = scaneightbitint();
	auto b = curval;
	scanoptionalequals();
	curval = scan_normal_dimen();
	if (box(b))
		mem[box(b)+c].int_ = curval;
}
