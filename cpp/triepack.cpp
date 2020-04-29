#include "triepack.h"
#include "firstfit.h"
#include "triepack.h"

void triepack(triepointer p)
{
	do
	{
		triepointer q = triel[p];
		if (q > 0 && triehash[q] == 0)
		{
			firstfit(q);
			triepack(q);
		}
		p = trier[p];
	}
	while (p);
}
