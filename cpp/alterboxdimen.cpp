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
	scandimen(false, false, false);
	if (box(b))
		mem[box(b)+c].int_ = curval;
}
