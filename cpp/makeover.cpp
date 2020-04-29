#include "makeover.h"
#include "cleanbox.h"
#include "overbar.h"

void makeover(halfword q)
{
	info(q+1) = overbar(cleanbox(q+1, 2*(curstyle/2)+1), 3*fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_, fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_);
	link(q+1) = 2;
}
