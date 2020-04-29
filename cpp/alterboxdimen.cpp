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
	if (eqtb[3678+b].hh.rh)
		mem[eqtb[3678+b].hh.rh+c].int_ = curval;
}
