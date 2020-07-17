#include "alterboxdimen.h"
#include "lecture.h"

void alterboxdimen(halfword chr, halfword align)
{
	auto c = chr;
	auto b = scaneightbitint(align);
	scanoptionalequals(align);
	int val = scan_normal_dimen(align);
	if (box(b))
		mem[box(b)+c].int_ = val;
}
