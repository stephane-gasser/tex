#include "inittrie.h"
#include "firstfit.h"
#include "compresstrie.h"
#include "triepack.h"
#include "triefix.h"

void inittrie(void)
{
	triepointer p;
	int j, k, t;
	triepointer r, s;
	twohalves h;
	opstart[0] = 0;
	for (j = 1; j <= 255; j++)
		opstart[j] = opstart[j-1]+trieused[j-1];
	for (j = 1; j <= trieopptr; j++)
		trieophash[j] = opstart[trieoplang[j]]+trieopval[j];
	for (j = 1; j <= trieopptr; j++)
		while (trieophash[j] > j)
		{
			k = trieophash[j];
			t = hyfdistance[k];
			hyfdistance[k] = hyfdistance[j];
			hyfdistance[j] = t;
			t = hyfnum[k];
			hyfnum[k] = hyfnum[j];
			hyfnum[j] = t;
			t = hyfnext[k];
			hyfnext[k] = hyfnext[j];
			hyfnext[j] = t;
			trieophash[j] = trieophash[k];
			trieophash[k] = k;
		}
	for (p = 0; p <= triesize; p++)
		triehash[p] = 0;
	trie_root = compresstrie(trie_root);
	for (p = 0; p <= trieptr; p++)
		trie_ref[p] = 0;
	for (p = 0; p <= 255; p++)
		triemin[p] = p+1;
	trie_link(0) = 1;
	triemax = 0;
	if (trie_root)
	{
		firstfit(trie_root);
		triepack(trie_root);
	}
	h.rh = 0;
	h.b0 = 0;
	h.b1 = 0;
	if (trie_root == 0)
	{
		for (r = 0; r < 256; r++)
			trie[r] = h;
		triemax = 256;
	}
	else
	{
		triefix(trie_root);
		r = 0;
		do
		{
			s = trie_link(r);
			trie[r] = h;
			r = s;
		} while (r <= triemax);
	}
	trie_char(0) = '?';
	trienotready = false;
}
