#include "triefix.h"

void triefix(triepointer p)
{
	triepointer z = trie_ref[p];
	do
	{
		triepointer q = triel[p];
		ASCIIcode c = triec[p];
		trie_link(z+c) = trie_ref[q];
		trie_char(z+c) = c;
		trie_op(z+c) = trieo[p];
		if (q > 0)
			triefix(q);
		p = trier[p];
	} while (p);
}
