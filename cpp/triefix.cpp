#include "triefix.h"

void triefix(triepointer p)
{
	triepointer z = triehash[p];
	do
	{
		triepointer q = triel[p];
		ASCIIcode c = triec[p];
		trie[z+c].rh = triehash[q];
		trie[z+c].b1 = c;
		trie[z+c].b0 = trieo[p];
		if (q > 0)
			triefix(q);
		p = trier[p];
	} while (p);
}
