#include "firstfit.h"
#include "overflow.h"

static halfword& trie_back(halfword p) { return trie[p].lh; }

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
				trie_link(triemax) = triemax+1;
				trie_back(triemax) = triemax-1;
			} while (triemax != h+256);
		}
		if (trietaken[h])
		{
			z = trie_link(z);
			continue;
		}
		q = trier[p];
		while (q > 0)
		{
			if (trie_link(h+triec[q]) == 0)
			{
				z = trie_link(z);
				continue;
			}
			q = trier[q];
		}
		break;
	}
	trietaken[h] = true;
	trie_ref[p] = h;
	q = p;
	do
	{
		z = h+triec[q];
		l = trie_back(z);
		r = trie_link(z);
		trie_back(r) = l;
		trie_link(l) = r;
		trie_link(z) = 0;
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
