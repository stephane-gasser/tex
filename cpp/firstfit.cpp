#include "firstfit.h"
#include "overflow.h"

void firstfit(triepointer p)
{
	triepointer h, z, q, l, r;
	int ll;
	ASCIIcode c = triec[p];
	z = triemin[c];
	while (true)
	{
		h = z-c;
		if (triemax < h+256)
		{
			if (triesize <= h+256)
				overflow("pattern memory", triesize);
			do
			{
				triemax++;
				trietaken[triemax] = false;
				trie[triemax].rh = triemax+1;
				trie[triemax].lh = triemax-1;
			} while (triemax != h+256);
		}
		if (trietaken[h])
		{
			z = trie[z].rh;
			continue;
		}
		q = trier[p];
		while (q > 0)
		{
			if (trie[h+triec[q]].rh == 0)
			{
				z = trie[z].rh;
				continue;
			}
			q = trier[q];
		}
		break;
	}
	trietaken[h] = true;
	triehash[p] = h;
	q = p;
	do
	{
		z = h+triec[q];
		l = trie[z].lh;
		r = trie[z].rh;
		trie[r].lh = l;
		trie[l].rh = r;
		trie[z].rh = 0;
		if (l < 256)
		{
			if (z < 256)
				ll = z;
			else
				ll = 256;
			do
			{
				triemin[l] = r;
				l++;
			} while (l == ll);
		}
		q = trier[q];
	} while (q);
}
