#include "eqworddefine.h"
#include "geqworddefine.h"
#include "sauvegarde.h"

void eqworddefine(halfword p, int w)
{
	if (xeqlevel[p] != curlevel)
	{
		eqsave(p, xeqlevel[p]);
		xeqlevel[p] = curlevel;
	}
	eqtb[p].int_ = w;
}

void word_define(int a, halfword p, int w)
{
	if (a >= 4)
		geqworddefine(p, w);
	else 
		eqworddefine(p, w);
}
