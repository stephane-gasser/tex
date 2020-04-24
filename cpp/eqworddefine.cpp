#include "eqworddefine.h"
#include "eqsave.h"

void eqworddefine(halfword p, int w)
{
	if (xeqlevel[p] != curlevel)
	{
		eqsave(p, xeqlevel[p]);
		xeqlevel[p] = curlevel;
	}
	eqtb[p].int_ = w;
}
