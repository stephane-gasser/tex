#include "fixlanguage.h"
#include "newwhatsit.h"
#include "normmin.h"

void fixlanguage(void)
{
	ASCIIcode l;
	if (eqtb[5313].int_ <= 0)
		l = 0;
	else 
		if (eqtb[5313].int_ > 255)
			l = 0;
		else
			l = eqtb[5313].int_;
	if (l != curlist.auxfield.hh.rh)
	{
		newwhatsit(4, 2);
		link(curlist.tailfield+1) = l;
		curlist.auxfield.hh.rh = l;
		type(curlist.tailfield+1) = normmin(eqtb[5314].int_);
		subtype(curlist.tailfield+1) = normmin(eqtb[5315].int_);
	}
}
