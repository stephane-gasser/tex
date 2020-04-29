#include "starteqno.h"
#include "pushmath.h"
#include "eqworddefine.h"
#include "begintokenlist.h"

void starteqno(void)
{
	savestack[saveptr++].int_ = curchr;
	pushmath(15);
	eqworddefine(5307, -1);
	if (eqtb[3415].hh.rh)
		begintokenlist(eqtb[3415].hh.rh, 8);
}
