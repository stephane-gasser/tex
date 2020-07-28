#include "cesure.h"
#include "erreur.h"
#include "noeud.h"
#include "lecture.h"
#include "impression.h"
#include "police.h"

static std::map<TrieNode, triepointer> tnMap;

static triepointer trienode(triepointer p)
{
	auto q = tnMap.find(trieNode[p]);
	if (q == tnMap.end())
	{
		tnMap[trieNode[p]] = p;
		return p;
	}
	return q->second;
}

static triepointer compresstrie(triepointer p)
{
	if (p == 0)
		return 0;
	trieNode[p].l = compresstrie(trieNode[p].l);
	trieNode[p].r = compresstrie(trieNode[p].r);
	return trienode(p);
}

static halfword& trie_link(halfword p) { return trie[p].hh.rh; }  //!< ``downward'' link in a trie
static quarterword& trie_char(halfword p) { return trie[p].hh.b1; } //!< character matched at this trie location
static quarterword& trie_op(halfword p) { return trie[p].hh.b0; } //!< program for hyphenation at this trie location

static void triefix(triepointer p)
{
	auto z = tnMap[trieNode[p]];
	do
	{
		auto q = trieNode[p].l;
		auto c = trieNode[p].c;
		trie_link(z+c) = tnMap[trieNode[q]];
		trie_char(z+c) = c;
		trie_op(z+c) = trieNode[p].o;
		if (q > 0)
			triefix(q);
		p = trieNode[p].r;
	} while (p);
}

//! backward links in |trie| holes
static halfword& trie_back(halfword p) { return trie[p].hh.lh; }

static std::map<ASCIIcode, triepointer> triemin;

static void firstfit(triepointer p)
{
	triepointer h, q;
	ASCIIcode c = trieNode[p].c;
	auto z = triemin[c];
	while (true)
	{
		h = z-c;
		if (trie.size()-1 < h+256)
		{
			if (trie.size()-1 <= h+256)
				overflow("pattern memory", triesize);
			do
			{
				Trie t;
				t.taken = false;
				trie.push_back(t);
				trie_link(trie.size()-1) = trie.size();
				trie_back(trie.size()-1) = trie.size()-2;
			} while (trie.size()-1 != h+256);
		}
		if (trie[h].taken)
		{
			z = trie_link(z);
			continue;
		}
		for (q = trieNode[p].r; q > 0; q = trieNode[q].r)
			if (trie_link(h+trieNode[q].c) == 0)
			{
				z = trie_link(z);
				continue;
			}
		break;
	}
	trie[h].taken = true;
	tnMap[trieNode[p]] = h;
	q = p;
	do
	{
		z = h+trieNode[q].c;
		auto l = trie_back(z);
		auto r = trie_link(z);
		trie_back(r) = l;
		trie_link(l) = r;
		trie_link(z) = 0;
		if (l < 256)
		{
			int ll = std::min(z, 256);
			do
			{
				triemin[l] = r;
				l++;
			} while (l != ll);
		}
		q = trieNode[q].r;
	} while (q);
}

static void triepack(triepointer p)
{
	for (; p; p = trieNode[p].r)
		if (auto q = trieNode[p].l; q > 0 && tnMap[trieNode[q]] == 0)
		{
			firstfit(q);
			triepack(q);
		}
}

static std::map<TrieOp, int> tOpMap;

void inittrie(void)
{
	opstart[0] = 0;
	for (int j = 1; j <= 255; j++)
		opstart[j] = opstart[j-1]+trieused[j-1];
	for (int j = 1; j < trieOp.size(); j++)
		tOpMap[trieOp[j]] = opstart[trieOp[j].lang]+trieOp[j].val;
	for (int j = 1; j < trieOp.size(); j++)
		while (tOpMap[trieOp[j]] > j)
		{
			auto k = tOpMap[trieOp[j]];
			std::swap(trieOp[k].hyfdistance, trieOp[j].hyfdistance);
			std::swap(trieOp[k].hyfnum,  trieOp[j].hyfnum);
			std::swap(trieOp[k].hyfnext, trieOp[j].hyfnext);
			std::swap(tOpMap[trieOp[j]], tOpMap[trieOp[k]]);
		}
	trie_root = compresstrie(trie_root);
	tnMap.clear();
	for (triepointer p = 0; p <= 255; p++)
		triemin[p] = p+1;
	trie_link(0) = 1;
	if (trie_root)
	{
		firstfit(trie_root);
		triepack(trie_root);
	}
	if (trie_root)
	{
		triefix(trie_root);
		for (triepointer r = 0, s; r < trie.size(); r = s)
		{
			s = trie_link(r);
			trie[r].hh = twohalves{0, 0};
		}
	}
	else
		for (triepointer r = 0; r < 256; r++)
			trie.push_back(Trie{false, twohalves{0, 0}});
	trie_char(0) = '?';
	trienotready = false;
}

quarterword newtrieop(smallnumber d, smallnumber n, quarterword v)
{
	TrieOp to;
	to.hyfdistance = d;
	to.hyfnum = n;
	to.hyfnext = v;
	to.lang = curlang;
	int l = tOpMap[to];
	if (l == 0)
	{
		to.val = ++trieused[curlang];
		trieOp.push_back(to);
		tOpMap[to] = trieOp.size()-1;
		return to.val;
	}
	return trieOp[l].val;
}

static void advance_major_tail(halfword &majortail, int &rcount)
{
	majortail = link(majortail);
	rcount++;
}

static void set_cur_r(int j, int n, halfword &curr, halfword &currh, halfword hchar)
{
	curr = j < n ? hu[j+1] : bchar;
	currh = hyf[j]%2 ? hchar : non_char;
}

static void wrap_lig(bool test, halfword &t)
{
	if (ligaturepresent)
	{
		halfword p = newligature(hf, curl, link(curq));
		if (lfthit)
		{
			subtype(p) = 2;
			lfthit = false;
		}
		if (test && ligstack == 0)
		{
			subtype(p)++;
			rthit = false;
		}
		link(curq) = p;
		t = p;
		ligaturepresent = false;
	}
}

static void pop_lig_stack(smallnumber &j, halfword &t)
{
	if (lig_ptr(ligstack) > 0)
	{
		link(t) = lig_ptr(ligstack);
		t = link(t);
		j++;
	}
}

static smallnumber reconstitute(smallnumber j, smallnumber n, halfword bchar, halfword hchar)
{
	halfword p, t;
	halfword currh, testchar;
	scaled w;
	fontindex k;
	hyphenpassed = 0;
	t = hold_head;
	w = 0;
	link(hold_head) = 0;
	curl = hu[j];
	curq = t;
	if (j == 0)
	{
		ligaturepresent = initlig;
		p = initlist;
		if (ligaturepresent)
			lfthit = initlft;
		while (p > 0)
		{
			link(t) = getavail();
			t = link(t);
			font(t) = hf;
			character(t) = character(p);
			p = link(p);
		}
	}
	else 
		if (curl < non_char)
		{
			link(t) = getavail();
			t = link(t);
			font(t) = hf;
			character(t) = curl;
		}
	ligstack = 0;
	set_cur_r(j, n, curr, currh, hchar);
	bool skipLoop;
	bool recommence;
	do
	{
		recommence = false;
		skipLoop = false;
		if (curl == 256)
		{
			k = fonts[hf].bcharlabel;
			if (k == 0)
				skipLoop = true;
		}
		else
		{
			if (fonts[hf].char_tag(curl) != lig_tag)
				skipLoop = true;
			else
			{
				k = fonts[hf].lig_kern_start(fonts[hf].char_info(curl));
				if (Font::skip_byte(k) > stop_flag)
					k = fonts[hf].lig_kern_restart(Font::infos(k));
			}
		}
		if (!skipLoop)
			testchar = currh < non_char ? currh : curr;
		while (!skipLoop)
		{
			if (Font::next_char(k) == testchar)
				if (Font::skip_byte(k) <= stop_flag)
					if (currh < non_char)
					{
						hyphenpassed = j;
						hchar = non_char;
						currh = non_char;
						recommence = true;
						break;
					}
					else
					{
						if (hchar < non_char && hyf[j]%2)
						{
							hyphenpassed = j;
							hchar = non_char;
						}
						if (Font::op_byte(k) < kern_flag)
						{
							if (curl == non_char)
								lfthit = true;
							if (j == n && ligstack == 0)
								rthit = true;
							switch (Font::op_byte(k))
							{
								// AB -> CB (symboles =:| et =:|>)
								case 1:
								case 5:
									curl = Font::rem_byte(k);
									ligaturepresent = true;
									break;
								// AB -> AC (symboles |=: et |=:>)
								case 2:
								case 6:
									curr = Font::rem_byte(k);
									if (ligstack > 0)
										character(ligstack) = curr;
									else
									{
										ligstack = newligitem(curr);
										if (j == n)
											bchar = non_char;
										else
										{
											p = getavail();
											lig_ptr(ligstack) = p;
											character(p) = hu[j+1];
											font(p) = hf;
										}
									}
									break;
								// AB -> ACB (symbole |=:|)
								case 3:
									curr = Font::rem_byte(k);
									p = ligstack;
									ligstack = newligitem(curr);
									link(ligstack) = p;
									break;
								// AB -> ACB (symboles |=:|> et |=:|>>)
								case 7:
								case 11:
									wrap_lig(false, t);
									curq = t;
									curl = Font::rem_byte(k);
									ligaturepresent = true;
									break;
								// AB -> C (symbole !=)
								default:
									curl = Font::rem_byte(k);
									ligaturepresent = true;
									if (ligstack > 0)
									{
										pop_lig_stack(j, t);
										p = ligstack;
										ligstack = link(p);
										freenode(p, 2);
										if (ligstack == 0)
											set_cur_r(j, n, curr, currh, hchar);
										else
											curr = character(ligstack);
									}
									else 
										if (j == n)
										{
											skipLoop = true;
											continue;
										}
										else
										{
											link(t) = getavail();
											t = link(t);
											font(t) = hf;
											character(t) = curr;
											j++;
											set_cur_r(j, n, curr, currh, hchar);
										}
							}
							if (Font::op_byte(k) > 4 && Font::op_byte(k) != 7)
							{
								skipLoop = true;
								continue;
							}
							recommence = true;
							break;
						}
						w = fonts[hf].char_kern(Font::infos(k));
						skipLoop = true;
						continue;
					}
			if (Font::skip_byte(k) >= 128)
				if (currh == 256)
				{
					skipLoop = true;
					continue;
				}
				else
				{
					currh = 256;
					recommence = true;
					break;
				}
			k += Font::skip_byte(k)+1;
		}
		if (recommence)
			continue;
		wrap_lig(rthit, t);
		if (w)
		{
			link(t) = newkern(w);
			t = link(t);
			w = 0;
		}
		if (ligstack > 0)
		{
			curq = t;
			curl = character(ligstack);
			ligaturepresent = true;
			pop_lig_stack(j, t);
			p = ligstack;
			ligstack = link(p);
			freenode(p, 2);
			if (ligstack == 0)
				set_cur_r(j, n, curr, currh, hchar);
			else
				curr = character(ligstack);
			recommence = true;
			continue;
		}
	} while (recommence);
	return j;
}

void hyphenate(void)
{
	char i, j, l;
	ASCIIcode c;
	for (j = 0; j <= hn; j++)
		hyf[j] = 0;
	auto h = hc[1];
	hn++;
	hc[hn] = curlang;
	for (j = 2; j <= hn; j++)
		h = (2*h+hc[j])%hyph_size;
	bool skip = false;
	halfword s;
	for (bool keepIn = true; keepIn;)
	{
		if (hyphword[h] == "")
			break;
		if (hyphword[h].size() < hn)
			break;
		if (hyphword[h].size() == hn)
		{
			j = 1;
			poolpointer u = 0;
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
			auto z = trie_link(curlang+1)+hc[j];
			l = j;
			while (hc[l] == trie_char(z))
			{
				if (trie_op(z))
				{
					auto v = trie_op(z);
					do
					{
						v += opstart[curlang];
						i = l-trieOp[v].hyfdistance;
						if (trieOp[v].hyfnum > hyf[i])
							hyf[i] = trieOp[v].hyfnum;
						v = trieOp[v].hyfnext;
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
	auto q = link(hb);
	link(hb) = 0;
	auto r = link(ha);
	link(ha) = 0;
	auto bchar = hyfbchar;
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
				auto majortail = r;
				auto rcount = 0;
				while (link(majortail) > 0)
					advance_major_tail(majortail, rcount);
				i = hyphenpassed;
				hyf[i] = 0;
				auto minortail = 0;
				info(r+1) = 0;
				auto hyfnode = newcharacter(hf, hyfchar);
				if (hyfnode)
				{
					i++;
					c = hu[i];
					hu[i] = hyfchar;
					free_avail(hyfnode);
				}
				while (l <= i)
				{
					l = reconstitute(l, i, fonts[hf].bchar, non_char)+1;
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
				char cloc = 0;
				if (fonts[hf].bcharlabel)
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

void newpatterns(Token t)
{
	char k, l;
	bool digitsensed;
	quarterword v;
	bool firstchild;
	ASCIIcode c;
	if (trienotready)
	{
		curlang = cur_fam();
		if (curlang <= 0 || curlang > 255)
				curlang = 0;
		auto t = scanleftbrace();
		k = 0;
		hyf[0] = 0;
		digitsensed = false;
		bool keepIn = true;
		while (keepIn)
		{
			auto t = getxtoken();
			switch (t.cmd)
			{
				case letter:
				case other_char:
					if (digitsensed || t.chr < '0' || t.chr > '9')
					{
						if (t.chr == '.')
							t.chr = 0;
						else
						{
							t.chr = lc_code(t.chr);
							if (t.chr == 0)
								error("Nonletter", "(See Appendix H.)");
						}
						if (k < 63)
						{
							k++;
							hc[k] = t.chr;
							hyf[k] = 0;
							digitsensed = false;
						}
					}
					else 
						if (k < 63)
						{
							hyf[k] = t.chr-'0';
							digitsensed = true;
						}
					break;
				case spacer:
				case right_brace:
					if (k > 0)
					{
						if (hc[1] == 0)
							hyf[0] = 0;
						if (hc[k] == 0)
							hyf[k] = 0;
						l = k;
						v = 0;
						while (true)
						{
							if (hyf[l] != 0)
							v = newtrieop(k-l, hyf[l], v);
							if (l > 0)
								l--;
							else
								break;
						}
						auto q = 0;
						hc[0] = curlang;
						while (l <= k)
						{
							c = hc[l];
							l++;
							auto p = trieNode[q].l;
							firstchild = true;
							while (p > 0 && c > trieNode[p].c)
							{
								q = p;
								p = trieNode[q].r;
								firstchild = false;
							}
							if (p == 0 || c < trieNode[p].c)
							{
								TrieNode tn;
								tn.r = p;
								tn.l = 0;
								tn.c = c;
								tn.o = 0;
								trieNode.push_back(tn);
								p = trieNode.size()-1;
								if (firstchild)
									trieNode[q].l = p;
								else
									trieNode[q].r = p;
							}
							q = p;
						}
						if (trieNode[q].o)
							error("Duplicate pattern", "(See Appendix H.)");
						trieNode[q].o = v;
					}
					if (t.cmd == right_brace)
					{
						keepIn = false;
						continue;
					}
					k = 0;
					hyf[0] = 0;
					digitsensed = false;
					break;
				default:
					error("Bad "+esc("patterns"), "(See Appendix H.)");
			}
		}
	}
	else
	{
		error("Too late for "+esc("patterns"), "All patterns must be given before typesetting begins.");
		link(garbage) = scantoks(false, false, t);
		flushlist(defref);
	}
}

