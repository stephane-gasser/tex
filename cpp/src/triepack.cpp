#include "triepack.h"
#include "firstfit.h"

void triepack(triepointer p)
{
	do
	{
		auto q = triel[p];
		if (q > 0 && trie_ref[q] == 0)
		{
			firstfit(q);
			triepack(q);
		}
		p = trier[p];
	} while (p);
}
