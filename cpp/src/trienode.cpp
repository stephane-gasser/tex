#include "trienode.h"

triepointer trienode(triepointer p)
{
	triepointer h = abs(triec[p]+1009*trieo[p]+2718*triel[p]+3142*trier[p])%triesize;
	while (true)
	{
		triepointer q = triehash[h];
		if (q == 0)
		{
			triehash[h] = p;
			return p;
		}
		if (triec[q] == triec[p] && trieo[q] == trieo[p] && triel[q] == triel[p] && trier[q] == trier[p])
		{
			return q;
		}
		if (h > 0)
			h--;
		else
			h = triesize;
	}
}
