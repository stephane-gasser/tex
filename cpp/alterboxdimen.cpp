#include "alterboxdimen.h"
#include "scaneightbitint.h"
#include "scanoptionalequals.h"
#include "scandimen.h"

void alterboxdimen(void)
{
	auto c = curchr;
	scaneightbitint();
	auto b = curval;
	scanoptionalequals();
	scan_normal_dimen();
	if (box(b))
		mem[box(b)+c].int_ = curval;
}
