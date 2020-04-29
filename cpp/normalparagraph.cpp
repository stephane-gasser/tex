#include "normalparagraph.h"
#include "eqworddefine.h"
#include "eqdefine.h"

void normalparagraph(void)
{
	if (eqtb[5282].int_)
		eqworddefine(5282, 0);
	if (eqtb[5847].int_)
		eqworddefine(5847, 0);
	if (eqtb[5304].int_ != 1)
		eqworddefine(5304, 1);
	if (eqtb[3412].hh.rh)
		eqdefine(3412, 118, 0);
}
