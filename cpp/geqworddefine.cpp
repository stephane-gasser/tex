#include "geqworddefine.h"

void geqworddefine(halfword p, int w)
{
	eqtb[p].int_ = w;
	xeqlevel[p] = 1;
}
