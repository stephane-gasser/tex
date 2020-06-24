#include "hyphenate.h"
#include "flushnodelist.h"
#include "freenode.h"
#include "reconstitute.h"
#include "getnode.h"
#include "newcharacter.h"
#include "flushlist.h"
#include "texte.h"

static void advance_major_tail(halfword &majortail, int &rcount)
{
	majortail = link(majortail);
	rcount++;
}


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
	poolpointer u;
	for (j = 0; j <= hn; j++)
		hyf[j] = 0;
	h = hc[1];
	hn++;
	hc[hn] = curlang;
	for (j = 2; j <= hn; j++)
	h = (2*h+hc[j])%hyph_size;
	bool keepIn = true;
	bool skip = false;
	while (keepIn)
	{
		if (hyphword[h] == "")
			break;
		if (hyphword[h].size() < hn)
			break;
		if (hyphword[h].size() == hn)
		{
			j = 1;
			u = 0;
			do
			{
				if (hyphword[h][u] < hc[j])
				{
					keepIn = false;
					continue;
				}
				if (hyphword[h][u] > hc[j])
				{
					if (h > 0)
						h--;
					else
						h = hyph_size;
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
			h = hyph_size;
	}
	if (!skip)
	{
		hn--;
		if (trie_char(curlang+1) != curlang)
			return;
		hc[0] = 0;
		hc[hn+1] = 0;
		hc[hn+2] = 256;
		for (j = 0; j <= hn-rhyf+1; j++)
		{
			z = trie_link(curlang+1)+hc[j];
			l = j;
			while (hc[l] == trie_char(z))
			{
				if (trie_op(z))
				{
					v =	trie_op(z);
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
				z = trie_link(z)+hc[l];
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
		if (is_char_node(ha))
			if (font(ha) != hf)
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
				hu[0] = character(ha);
			}
		else 
			if (type(ha) == ligature_node)
				if (font(lig_char(ha)) != hf)
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
					initlist = lig_ptr(ha);
					initlig = true;
					initlft = subtype(ha) > 1;
					hu[0] = character(lig_char(ha));
					if (initlist == 0 && initlft)
					{
						hu[0] = 256;
						initlig = false;
					}
					freenode(ha, small_node_size);
				}
			else
			{
				if (!is_char_node(r) && type(r) == ligature_node && subtype(r) > 1)
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
				r = getnode(small_node_size);
				link(r) = link(hold_head);
				type(r) = disc_node;
				majortail = r;
				rcount = 0;
				while (link(majortail) > 0)
					advance_major_tail(majortail, rcount);
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
					l = reconstitute(l, i, fontbchar[hf], non_char)+1;
					if (link(hold_head) > 0)
					{
						if (minortail == 0)
							pre_break(r) = link(hold_head);
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
				pre_break(r) = 0;
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
						l = reconstitute(l, hn, bchar, non_char)+1;
						if (cloc > 0)
						{
							hu[cloc] = c;
							cloc = 0;
						}
						if (link(hold_head) > 0)
						{
							if (minortail == 0)
								pre_break(r) = link(hold_head);
							else
								link(minortail) = link(hold_head);
							minortail = link(hold_head);
							while (link(minortail) > 0)
								minortail = link(minortail);
						}
					} while (l < j);
					while (l > j)
					{
						j = reconstitute(j, hn, bchar, non_char)+1;
						link(majortail) = link(hold_head);
						while (link(majortail) > 0)
							advance_major_tail(majortail, rcount);
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
