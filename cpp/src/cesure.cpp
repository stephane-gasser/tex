#include "cesure.h"
#include "erreur.h"
#include "noeud.h"
#include "lecture.h"
#include "impression.h"
#include "police.h" 
#include "equivalent.h" 
#include "chaine.h" 

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

static quarterword newtrieop(smallnumber d, smallnumber n, quarterword v)
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

static void advance_major_tail(LinkedNode *majortail, int &rcount)
{
	next(majortail);
	rcount++;
}

static char hyf[65]; // of 0..9 //odd values indicate discretionary hyphens
static bool lfthit = false, rthit = false; //!< did we hit a ligature with a boundary character?

static void set_cur_r(int j, int n, halfword &curr, halfword &currh, halfword hchar)
{
	curr = j < n ? hu[j+1] : bchar;
	currh = hyf[j]%2 ? hchar : non_char;
}

static halfword curl, curr; //!< characters before and after the cursor
static LinkedNode *curq; //!< where a ligature should be detached
static CharNode *ligstack; //!< unfinished business to the right of the cursor


static void wrap_lig(bool test, LinkedNode *t)
{
	if (ligaturepresent)
	{
		auto p = new LigatureNode(hf, curl, curq->link);
		if (lfthit)
		{
			p->subtype = 2;
			lfthit = false;
		}
		if (test && ligstack == nullptr)
		{
			p->subtype++;
			rthit = false;
		}
		curq->link = p;
		t = p;
		ligaturepresent = false;
	}
}

static void pop_lig_stack(smallnumber &j, LinkedNode *t)
{
	if (auto l = dynamic_cast<LigatureNode*>(ligstack)->lig_ptr; l)
	{
		appendAtEnd(t, l);
		j++;
	}
}

static CharNode *initlist;
static bool initlig;
static bool initlft;
static smallnumber hyphenpassed;

static smallnumber reconstitute(smallnumber j, smallnumber n, halfword bchar, halfword hchar)
{
	halfword currh; // hyphen character for ligature testing
	halfword testchar; // hyphen or other character for ligature testing
	scaled w;
	hyphenpassed = 0;
	w = 0;
	hold_head->link = nullptr;
	curl = hu[j];
	auto t = hold_head;
	curq = hold_head;
	if (j == 0)
	{
		ligaturepresent = initlig;
		if (ligaturepresent)
			lfthit = initlft;
		for (auto p = initlist; p; next(p))
			appendAtEnd(t, new CharNode(hf, p->character));
	}
	else 
		if (curl < non_char)
			appendAtEnd(t, new CharNode(hf, curl));
	ligstack = nullptr;
	set_cur_r(j, n, curr, currh, hchar);
	bool skipLoop;
	bool recommence;
	do
	{
		recommence = false;
		skipLoop = false;
		fontindex k;
		if (curl == non_char)
		{
			k = fonts[hf].bcharlabel;
			if (k == non_address)
				skipLoop = true;
		}
		else
		{
			if (fonts[hf].char_tag(curl) != lig_tag)
				skipLoop = true;
			else
				k = fonts[hf].lig_kern_first(curl);
		}
		if (!skipLoop)
			testchar = currh < non_char ? currh : curr;
		for (; !skipLoop; k += Font::skip_byte(k)+1)
		{
			if (Font::next_char(k) == testchar && Font::skip_byte(k) <= stop_flag)
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
						if (j == n && ligstack == nullptr)
							rthit = true;
						switch (Font::op_byte(k))
						{
							case AB_cB: skipLoop = true; [[fallthrough]];
							case AB_CB:
								curl = Font::rem_byte(k);
								ligaturepresent = true;
								break;
							case AB_aC: skipLoop = true; [[fallthrough]];
							case AB_AC:
								curr = Font::rem_byte(k);
								if (ligstack)
									dynamic_cast<LigatureNode*>(ligstack)->character = curr;
								else
								{
									ligstack = new LigatureNode(curr);
									if (j == n)
										bchar = non_char;
									else
										dynamic_cast<LigatureNode*>(ligstack)->lig_ptr = new CharNode(hf, hu[j+1]);
								}
								break;
							case AB_ACB:
							{
								curr = Font::rem_byte(k);
								auto p = new CharNode(ligstack->font, ligstack->character);
								ligstack = new LigatureNode(curr);
								ligstack->link = p;
								break;
							}
							case AB_acB: skipLoop = true; [[fallthrough]];
							case AB_aCB:
								wrap_lig(false, t);
								curq = t;
								curl = Font::rem_byte(k);
								ligaturepresent = true;
								break;
							case AB_C:
								curl = Font::rem_byte(k);
								ligaturepresent = true;
								if (ligstack)
								{
									pop_lig_stack(j, t);
									auto p = ligstack;
									next(ligstack);
									delete p;
									if (ligstack == nullptr)
										set_cur_r(j, n, curr, currh, hchar);
									else
										curr = dynamic_cast<LigatureNode*>(ligstack)->character;
								}
								else 
									if (j == n)
									{
										skipLoop = true;
										continue;
									}
									else
									{
										appendAtEnd(t, new CharNode(hf, curr));
										j++;
										set_cur_r(j, n, curr, currh, hchar);
									}
						}
						if (skipLoop)
							continue;
						recommence = true;
						break;
					}
					w = fonts[hf].char_kern(k);
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
		}
		if (recommence)
			continue;
		wrap_lig(rthit, t);
		if (w)
			appendAtEnd(t, new KernNode(w));
		w = 0;
		if (ligstack)
		{
			curq = t;
			curl = dynamic_cast<LigatureNode*>(ligstack)->character;
			ligaturepresent = true;
			pop_lig_stack(j, t);
			auto p = ligstack;
			next(ligstack);
			delete p;
			if (ligstack == nullptr)
				set_cur_r(j, n, curr, currh, hchar);
			else
				curr = dynamic_cast<LigatureNode*>(ligstack)->character;
			recommence = true;
			continue;
		}
	} while (recommence);
	return j;
}

void hyphenate(LinkedNode *curp)
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
			HyphenNode *s;
			for (s = hyphlist[h]; s; next(s))
				hyf[s->pos] = 1;
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
	auto q = hb->link;
	hb->link = nullptr;
	auto r = ha->link;
	ha->link = nullptr;
	auto bchar = hyfbchar;
	LinkedNode *s; 
	do
	{
		if (ha->is_char_node())
			if (dynamic_cast<CharNode*>(ha)->font != hf)
			{
				s = ha;
				j = 0;
				hu[0] = 256;
				initlig = false;
				initlist = nullptr;
				break;
			}
			else
			{
				initlist = dynamic_cast<CharNode*>(ha);
				initlig = false;
				hu[0] = dynamic_cast<CharNode*>(ha)->character;
			}
		else 
			if (ha->type == ligature_node)
				if (dynamic_cast<LigatureNode*>(ha)->font != hf)
				{
					s = ha;
					j = 0;
					hu[0] = 256;
					initlig = false;
					initlist = nullptr;
					break;
				}
				else
				{
					initlist = dynamic_cast<CharNode*>(dynamic_cast<LigatureNode*>(ha)->lig_ptr);
					initlig = true;
					initlft = dynamic_cast<LigatureNode*>(ha)->subtype > 1;
					hu[0] = dynamic_cast<LigatureNode*>(ha)->character;
					if (initlist == nullptr && initlft)
					{
						hu[0] = 256;
						initlig = false;
					}
					delete ha;
				}
			else
			{
				if (!r->is_char_node() && r->type == ligature_node && dynamic_cast<LigatureNode*>(r)->subtype > 1)
				{
					s = ha;
					j = 0;
					hu[0] = 256;
					initlig = false;
					initlist = nullptr;
					break;
				}
				j = 1;
				s = ha;
				initlist = nullptr;
				break;
			}
		s = curp;
		followUntilBeforeTarget(s, ha);
		j = 0;
	} while (false);
	flushnodelist(r);
	do
	{
		l = j;
		j = reconstitute(j, hn, bchar, hyfchar)+1;
		if (hyphenpassed == 0)
		{
			s->link = hold_head->link;
			followUntilBeforeTarget(s);
			if (hyf[j-1]%2)
			{
				l = j;
				hyphenpassed = j-1;
				hold_head->link = nullptr;
			}
		}
		if (hyphenpassed > 0)
			do
			{
				r = new DiscNode;
				r->link = hold_head->link;
				auto majortail = r;
				auto rcount = 0;
				while (majortail->link)
					advance_major_tail(majortail, rcount);
				i = hyphenpassed;
				hyf[i] = 0;
				LinkedNode *minortail = nullptr;
				dynamic_cast<DiscNode*>(r)->pre_break = nullptr;
				CharNode *hyfnode = newcharacter(hf, hyfchar);
				if (hyfnode)
				{
					i++;
					c = hu[i];
					hu[i] = hyfchar;
					delete hyfnode;
					hyfnode = nullptr;
				}
				while (l <= i)
				{
					l = reconstitute(l, i, fonts[hf].bchar, non_char)+1;
					if (hold_head->link)
					{
						if (minortail == nullptr)
							dynamic_cast<DiscNode*>(r)->pre_break = hold_head->link;
						else
							minortail->link = hold_head->link;
						minortail = hold_head->link;
						followUntilBeforeTarget(minortail);
					}
				}
				if (hyfnode)
				{
					hu[i] = c;
					l = i;
					i--;
				}
				minortail = 0;
				dynamic_cast<DiscNode*>(r)->pre_break = nullptr;
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
						if (hold_head->link)
						{
							if (minortail == nullptr)
								dynamic_cast<DiscNode*>(r)->pre_break = hold_head->link;
							else
								minortail->link = hold_head->link;
							minortail = hold_head->link;
							while (minortail->link)
								minortail = minortail->link;
						}
					} while (l < j);
					while (l > j)
					{
						j = reconstitute(j, hn, bchar, non_char)+1;
						majortail->link = hold_head->link;
						while (majortail->link)
							advance_major_tail(majortail, rcount);
					}
				}
				if (rcount > 127)
				{
					s->link = r->link;
					r->link = nullptr;
					flushnodelist(r);
				}
				else
				{
					s->link = r;
					dynamic_cast<DiscNode*>(r)->replace_count = rcount;
				}
				s = majortail;
				hyphenpassed = j-1;
				hold_head->link = nullptr;
			} while (hyf[j-1]%2);
	} while (j <= hn);
	s->link = q;
	flushnodelist(initlist);
}

void newpatterns(Token t)
{
	ASCIIcode c;
	if (trienotready)
	{
		curlang = cur_fam();
		if (curlang <= 0 || curlang > 255)
				curlang = 0;
		auto t = scanleftbrace();
		char k = 0;
		hyf[0] = 0;
		for (bool keepIn = true, digitsensed = false; keepIn;)
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
						
						char v = 0;
						char l;
						for (l = k; l >= 0; l--)
							if (hyf[l])
								v = newtrieop(k-l, hyf[l], v);
						auto q = 0;
						hc[0] = curlang;
						while (l <= k)
						{
							c = hc[l];
							l++;
							triepointer p;
							bool firstchild = true;
							for (p = trieNode[q].l; p > 0 && c > trieNode[p].c; p = trieNode[q].r)
							{
								firstchild = false;
								q = p;
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
		garbage->link = scantoks(false, false, t);
		flushnodelist(defref);
	}
}

void newhyphexceptions(void)
{
	char n, j;
	hyphpointer h;
	poolpointer u, v;
	auto t = scanleftbrace();
	curlang = cur_fam();
	if (curlang < 0 || curlang > 255)
		curlang = 0;
	n = 0;
	HyphenNode *p = nullptr;
	t = getxtoken();
	while (true)
	{
		switch (t.cmd)
		{
			case letter:
			case other_char:
			case char_given:
				if (t.chr == '-')
				{
					if (n < 63)
					{
						auto q = new HyphenNode;
						q->link = p;
						q->pos = n;
						p = q;
					}
				}
				else 
					if (lc_code(t.chr) == 0)
						error("Not a letter", "Letters in \\hyphenation words must have \\lccode>0.\nProceed; I'll ignore the character I just read.");
					else 
						if (n < 63)
						{
							n++;
							hc[n] = lc_code(t.chr);
						}
				break;
			case char_num:
				t.chr = scancharnum();
				t.cmd = char_given;
				continue;
			case spacer:
			case right_brace:
				if (n > 1)
				{
					n++;
					hc[n] = curlang;
					h = 0;
					std::string s;
					for (j = 1; j <= n; j++)
					{
						h = (2*h+hc[j])%hyph_size;
						s += hc[j];
					}
					if (hyphcount == hyph_size)
						overflow("exception dictionary", hyph_size);
					hyphcount++;
					while (hyphword[h] != "")
					{
						if (hyphword[h].size() < s.size())
						{
							std::swap(hyphlist[h], p);
							std::swap(hyphword[h], s);
						}
						else 
							if (hyphword[h].size() == s.size())
							{
								u = 0;
								v = 0;
								bool label45 = false;
								do
								{
									if (hyphword[h][u] < s[v])
									{
										std::swap(hyphlist[h], p);
										std::swap(hyphword[h], s);
										label45 = true;
									}
									if (hyphword[h][u] > s[v])
										label45 = true;
									if (label45)
										break;
									u++;
									v++;
								} while (u < hyphword[h].size());
								if (!label45)
								{
									std::swap(hyphlist[h], p);
									std::swap(hyphword[h], s);
								}
							}
						if (h > 0)
							h--;
						else
							h = hyph_size;
					}
					hyphword[h] = s;
					hyphlist[h] = p;
				}
				if (t.cmd == right_brace)
					return;
				n = 0;
				p = 0;
				break;
			default:
				error("Improper "+esc("hyphenation")+" will be flushed", "Hyphenation exceptions must contain only letters\nand hyphens. But continue; I'll forgive and forget.");
		}
		t = getxtoken();
	}
}
