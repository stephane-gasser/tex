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
	triel[0] = compresstrie(triel[0]);
	for (p = 0; p <= trieptr; p++)
		triehash[p] = 0;
	for (p = 0; p <= 255; p++)
		triemin[p] = p+1;
	trie[0].rh = 1;
	triemax = 0;
	if (triel[0])
	{
		firstfit(triel[0]);
		triepack(triel[0]);
	}
	h.rh = 0;
	h.b0 = 0;
	h.b1 = 0;
	if (triel[0] == 0)
	{
		for (r = 0; r < 256; r++)
			trie[r] = h;
		triemax = 256;
	}
	else
	{
		triefix(triel[0]);
		r = 0;
		do
		{
			s = trie[r].rh;
			trie[r] = h;
			r = s;
		} while (r <= triemax);
	}
	trie[0].b1 = 63;
	trienotready = false;
}
