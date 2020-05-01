#include "hyphenate.h"
#include "flushnodelist.h"
#include "freenode.h"
#include "reconstitute.h"
#include "getnode.h"
#include "newcharacter.h"
#include "flushlist.h"

void hyphenate(void)
{
	char i, j, l;
	halfword q, r, s, bchar, majortail, minortail;
	ASCIIcode c;
	char cloc;
	int rcount;
	halfword hyfnode;
	triepointer z;
	int v;
	hyphpointer h;
	strnumber k;
	poolpointer u;
	for (j = 0; j <= hn; j++)
		hyf[j] = 0;
	h = hc[1];
	hn++;
	hc[hn] = curlang;
	for (j = 2; j <= hn; j++)
	h = (h+h+hc[j])%307;
	bool keepIn = true;
	bool skip = false;
	while (keepIn)
	{
		k = hyphword[h];
		if (k == 0)
			break;
		if (strstart[k+1]-strstart[k] < hn)
			break;
		if (strstart[k+1]-strstart[k] == hn)
		{
			j = 1;
			u = strstart[k];
			do
			{
				if (strpool[u] < hc[j])
				{
					keepIn = false;
					continue;
				}
				if (strpool[u] > hc[j])
				{
					if (h > 0)
						h--;
					else
						h = 307;
					keepIn = false;
					continue;
				}
				j++;
				u++;
			} while (j <= hn);
			s = hyphlist[h];
			while (s)
			{
				hyf[info(s)] = 1;
				s = link(s);
			}
			hn--;
			skip = true;
			break;
		}
		if (h > 0)
			h--;
		else
			h = 307;
	}
	if (!skip)
	{
		hn--;
		if (trie[curlang+1].b1 != curlang)
			return;
		hc[0] = 0;
		hc[hn+1] = 0;
		hc[hn+2] = 256;
		for (j = 0; j <= hn-rhyf+1; j++)
		{
			z = trie[curlang+1].rh+hc[j];
			l = j;
			while (hc[l] == trie[z].b1)
			{
				if (trie[z].b0)
				{
					v =	trie[z].b0;
					do
					{
						v += opstart[curlang];
						i = l-hyfdistance[v];
						if (hyfnum[v] > hyf[i])
							hyf[i] = hyfnum[v];
						v = hyfnext[v];
					} while (v);
				}
				l++;
				z = trie[z].rh+hc[l];
			}
		}
	}
	for (j = 0; j < lhyf; j++)
		hyf[j] = 0;
	for (j = 0; j < rhyf; j++)
		hyf[hn-j] = 0;
	bool fini = true;
	for (j = lhyf; j <= hn-rhyf; j++)
		if (hyf[j]%2)
			fini = false;
	if (fini)
		return;
	q = link(hb);
	link(hb) = 0;
	r = link(ha);
	link(ha) = 0;
	bchar = hyfbchar;
	do
	{
		if (ha >= himemmin)
			if (type(ha) != hf)
			{
				s = ha;
				j = 0;
				hu[0] = 256;
				initlig = false;
				initlist = 0;
				break;
			}
			else
			{
				initlist = ha;
				initlig = false;
				hu[0] = subtype(ha);
			}
		else 
			if (type(ha) == 6)
				if (type(ha+1) != hf)
				{
					s = ha;
					j = 0;
					hu[0] = 256;
					initlig = false;
					initlist = 0;
					break;
				}
				else
				{
					initlist = link(ha+1);
					initlig = true;
					initlft = subtype(ha) > 1;
					hu[0] = subtype(ha+1);
					if (initlist == 0 && initlft)
					{
						hu[0] = 256;
						initlig = false;
					}
					freenode(ha, 2);
				}
			else
			{
				if (r < himemmin && type(r) == 6 && subtype(r) > 1)
				{
					s = ha;
					j = 0;
					hu[0] = 256;
					initlig = false;
					initlist = 0;
					break;
				}
				j = 1;
				s = ha;
				initlist = 0;
				break;
			}
		s = curp;
		while (link(s) != ha)
			s = link(s);
		j = 0;
	} while (false);
	flushnodelist(r);
	do
	{
		l = j;
		j = reconstitute(j, hn, bchar, hyfchar)+1;
		if (hyphenpassed == 0)
		{
			link(s) = link(hold_head);
			while (link(s) > 0)
				s = link(s);
			if (hyf[j-1]%2)
			{
				l = j;
				hyphenpassed = j-1;
				link(hold_head) = 0;
			}
		}
		if (hyphenpassed > 0)
			do
			{
				r = getnode(2);
				link(r) = link(hold_head);
				type(r) = 7;
				majortail = r;
				rcount = 0;
				while (link(majortail) > 0)
				{
					majortail = link(majortail);
					rcount++;
				}
				i = hyphenpassed;
				hyf[i] = 0;
				minortail = 0;
				info(r+1) = 0;
				hyfnode = newcharacter(hf, hyfchar);
				if (hyfnode)
				{
					i++;
					c = hu[i];
					hu[i] = hyfchar;
					link(hyfnode) = avail;
					avail = hyfnode;
				}
				while (l <= i)
				{
					l = reconstitute(l, i, fontbchar[hf], 256)+1;
					if (link(hold_head) > 0)
					{
						if (minortail == 0)
							info(r+1) = link(hold_head);
						else
							link(minortail) = link(hold_head);
						minortail = link(hold_head);
						while (link(minortail) > 0)
							minortail = link(minortail);
					}
				}
				if (hyfnode)
				{
					hu[i] = c;
					l = i;
					i--;
				}
				minortail = 0;
				link(r+1) = 0;
				cloc = 0;
				if (bcharlabel[hf])
				{
					l--;
					c = hu[l];
					cloc = l;
					hu[l] = 256;
				}
				while (l < j)
				{
					do
					{
						l = reconstitute(l, hn, bchar, 256)+1;
						if (cloc > 0)
						{
							hu[cloc] = c;
							cloc = 0;
						}
						if (link(hold_head) > 0)
						{
							if (minortail == 0)
								link(r+1) = link(hold_head);
							else
								link(minortail) = link(hold_head);
							minortail = link(hold_head);
							while (link(minortail) > 0)
								minortail = link(minortail);
						}
					} while (l < j);
					while (l > j)
					{
						j = reconstitute(j, hn, bchar, 256)+1;
						link(majortail) = link(hold_head);
						while (link(majortail) > 0)
						{
							majortail = link(majortail);
							rcount++;
						}
					}
				}
				if (rcount > 127)
				{
					link(s) = link(r);
					link(r) = 0;
					flushnodelist(r);
				}
				else
				{
					link(s) = r;
					subtype(r) = rcount;
				}
				s = majortail;
				hyphenpassed = j-1;
				link(hold_head) = 0;
			} while (hyf[j-1]%2);
	} while (j <= hn);
	link(s) = q;
	flushlist(initlist);
}
