#include "cesure.h"
#include "erreur.h"
#include "noeud.h"
#include "lecture.h"
#include "impression.h"
#include "police.h" 
#include "equivalent.h" 
#include "chaine.h"

class PatternNode
{
	public:
		quarterword o = 0;
		std::map<char, PatternNode*> children;
};

std::vector<PatternNode*> patterns(256, nullptr);

/*class TrieNode
{
	public:
		packedASCIIcode c; //characters to match
		quarterword o = 0; //operations to perform
		triepointer l = 0; //left subtrie links
		triepointer r; //right subtrie links
		TrieNode(triepointer p = 0, packedASCIIcode C = 0) : c(C), r(p) {}
		bool operator == (const TrieNode &tn) const { return std::tuple(c, o, l, r) == std::tuple(tn.c, tn.o, tn.l, tn.r); }
		bool operator < (const TrieNode &tn) const { return std::tuple(c, o, l, r) < std::tuple(tn.c, tn.o, tn.l, tn.r); }
};

static std::map<TrieNode, triepointer> tnMap;
static std::vector<TrieNode> tn(1);
static triepointer &trie_root = tn[0].l; //!< root of the linked tr*/

static void savePattern(const std::string &pattern, quarterword hyfNext)
{
	auto P = patterns[curlang];
	if (P == nullptr)
		P = new PatternNode;
	for (char c: pattern)
		if (P->children.find(c) != P->children.end())
			P = P->children[c];
		else
		{
			P->children[c] = new PatternNode;
			P = P->children[c];
		}
	if (P->o)
		error("Duplicate pattern", "(See Appendix H.)");
	P->o = hyfNext;
	/*auto q = 0;
	for (int l = 0, c = curlang; l <= pattern.size(); c = pattern[l++])
	{
		auto p = tn[q].l;
		bool firstchild = p == 0 || c <= tn[p].c; //is |p=trie_l[q]|?
		if (firstchild)
		{
			if (p == 0 || c < tn[p].c) 
			{	//Insert a new tr node between |q| and |p|, and make |p| point to it
				tn.push_back(TrieNode(q, c));
				tn[q].l = p = tn.size()-1;
				q = p; //now node |q| represents $p_1\ldots p_{l-1}$
			}
		}
		else
		{
			for (; p > 0 && c > tn[p].c; q = p, p = tn[q].r);
			if (p == 0 || c < tn[p].c) 
			{	//Insert a new tr node between |q| and |p|, and make |p| point to it
				tn.push_back(TrieNode(p, c));
				tn[q].r = p = tn.size()-1;
				q = p; //now node |q| represents $p_1\ldots p_{l-1}$
			}
		}
	}
	if (tn[q].o)
		error("Duplicate pattern", "(See Appendix H.)");
	tn[q].o = hyfNext;*/
}

/*static triepointer trienode(triepointer p)
{
	auto q = tnMap.find(tn[p]);
	if (q == tnMap.end())
	{
		tnMap[tn[p]] = p;
		return p;
	}
	return q->second;
}

static triepointer compresstrie(triepointer p)
{
	if (p == 0)
		return 0;
	tn[p].l = compresstrie(tn[p].l);
	tn[p].r = compresstrie(tn[p].r);
	return trienode(p);
}*/

/*class Trie
{
	public:
		bool taken = false; //does a family start here
		halfword link = 0; //!< ``downward'' link in a tr
		quarterword char_ = 0; //!< character matched at this tr location
		quarterword op = 0; //!< program for hyphenation at this tr location
		halfword back = 0; //!< backward links in |tr| holes
};

static std::vector<Trie> tr(1);*/

/*static void triefix(triepointer p)
{
	auto z = tnMap[tn[p]];
	for (; p; p = tn[p].r)
	{
		auto q = tn[p].l;
		auto c = tn[p].c;
		tr[z+c].link = tnMap[tn[q]];
		tr[z+c].char_ = c;
		tr[z+c].op = tn[p].o;
		if (q > 0)
			triefix(q);
	}
}*/

/*static triepointer triemin[256]; //the first possible slot for each character

static void firstfit(triepointer p)
{
	triepointer h; //candidate for |trie_ref[p]
	ASCIIcode c = tn[p].c;
	auto z = triemin[c];
	while (true)
	{
		h = z-c;
		if (h+256 >= triesize)
			overflow("pattern memory", triesize);
		while (tr.size()-1 < h+256)
		{
			Trie t;
			tr.push_back(t);
			tr.back().link = tr.size();
			tr.back().back = tr.size()-2;
		}
		if (tr[h].taken)
		{
			z = tr[z].link;
			continue;
		}
		for (auto q = tn[p].r; q > 0; q = tn[q].r)
			if (tr[h+tn[q].c].link == 0)
			{
				z = tr[z].link;
				continue;
			}
		break;
	}
	tr[h].taken = true;
	tnMap[tn[p]] = h;
	auto q = p;
	do
	{
		z = h+tn[q].c;
		auto l = tr[z].back;
		auto r = tr[z].link;
		tr[r].back = l;
		tr[l].link = r;
		tr[z].link = 0;
		if (l < 256)
		{
			int ll = std::min(z, 256);
			do
			{
				triemin[l] = r;
				l++;
			} while (l < ll);
		}
		q = tn[q].r;
	} while (q);
}*/

/*static void triepack(triepointer p)
{
	for (; p; p = tn[p].r)
		if (auto q = tn[p].l; q > 0 && tnMap[tn[q]] == 0)
		{
			firstfit(q);
			triepack(q);
		}
}*/

class TrieOp
{
	public:
		ASCIIcode lang;
		quarterword val;
		quarterword hyfnext;
		smallnumber hyfnum;
		smallnumber hyfdistance;
		TrieOp(smallnumber d = 0, smallnumber n = 0, quarterword v = 0, ASCIIcode l = 0) : hyfdistance(d), hyfnum(n), hyfnext(v), lang(l) {}
		bool operator == (const TrieOp &to) const { return std::tuple(lang, hyfnext, hyfnum, hyfdistance) == std::tuple(to.lang, to.hyfnext, to.hyfnum, to.hyfdistance); }
		bool operator < (const TrieOp &to) const { return std::tuple(lang, hyfnext, hyfnum, hyfdistance) < std::tuple(to.lang, to.hyfnext, to.hyfnum, to.hyfdistance); }
};

static std::map<TrieOp, int> tOpMap; // indice d'un TrieOp dans le tableau trieOp
static std::vector<TrieOp> trieOp(1);

void inittrie(void)
{
/*	opstart[0] = 0;
	for (int lang = 1; lang <= 255; lang++)
		opstart[lang] = opstart[lang-1]+trieused[lang-1];
	for (auto &to: trieOp)
		tOpMap[to] = opstart[to.lang]+to.val;
	for (int j = 1; j < trieOp.size(); j++)
		while (tOpMap[trieOp[j]] > j)
		{
			auto &to = trieOp[j];
			auto &to2 = trieOp[tOpMap[to]];
			std::swap(to2.hyfdistance, to.hyfdistance);
			std::swap(to2.hyfnum,  to.hyfnum);
			std::swap(to2.hyfnext, to.hyfnext);
			std::swap(tOpMap[to], tOpMap[to2]);
		}
	trie_root = compresstrie(trie_root);
	tnMap.clear();
	for (triepointer p = 0; p <= 255; p++)
		triemin[p] = p+1;
	tr[0].link = 1;
	if (trie_root)
	{
		firstfit(trie_root);
		triepack(trie_root);
	}
	if (trie_root)
	{
		triefix(trie_root);
		for (triepointer r = 0, s; r < tr.size(); r = s)
		{
			s = tr[r].link;
			tr[r] = Trie();
		}
	}
	else
		for (triepointer r = 0; r < 256; r++)
			tr.push_back(Trie());
	tr[0].char_ = '?';*/
	trienotready = false;
}

static void advance_major_tail(LinkedNode *majortail, int &rcount)
{
	next(majortail);
	rcount++;
}

static unsigned char hyf[65]; // of 0..9 //odd values indicate discretionary hyphens
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
		auto p = new LigatureNode(hf, curl, dynamic_cast<CharNode*>(curq->link));
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

static std::map<std::string, HyphenNode*> exceptionList;

void hyphenate(LinkedNode *curp)
{
	std::fill_n(hyf, hn+1, 0);
	//Look for the word |hc[1..hn]| in the exception table, and |goto found| (with |hyf| containing the hyphens) if an entry is found
	std::string exception;
	for (int i = 1; i <= hn; i++)
		exception += hc[i];
	exception += char(curlang);
	bool found = exceptionList.find(exception) != exceptionList.end();
	if (found)
		for (auto s = exceptionList[exception]; s; next(s))
			hyf[s->pos] = 1;
	else
	{
		if (patterns[curlang] == nullptr)
			return;
/*		if (tr[curlang+1].char_ != curlang) //no patterns for |cur_lang|
			return;*/
		// insert delimiters
		/*hc[0] = 0;
		hc[hn+1] = 0;
		hc[hn+2] = 256;*/
		for (int debut = 0; debut+rhyf <= hn+1; debut++)
		{
			auto P = patterns[curlang];
			for (int l = debut; P->children.find(hc[l+1]) != P->children.end(); P = P->children[hc[1+l++]])
				for (auto v = P->o; v; v = trieOp[v].hyfnext) //Store maximum values in the |hyf| table
				{
					v += opstart[curlang];
					int i = l-trieOp[v].hyfdistance;
					hyf[i] = std::max(trieOp[v].hyfnum, hyf[i]);
				}
			/*auto z = tr[curlang+1].link+hc[debut];
			for (int l = debut; hc[l] == tr[z].char_; l++, z = tr[z].link+hc[l])
				for (auto v = tr[z].op; v; v = trieOp[v].hyfnext) //Store maximum values in the |hyf| table
				{
					v += opstart[curlang];
					int i = l-trieOp[v].hyfdistance;
					hyf[i] = std::max(trieOp[v].hyfnum, hyf[i]);
				}*/
		}
	}
	std::fill_n(hyf, lhyf, 0);
	std::fill_n(hyf+hn-rhyf+1, rhyf, 0);
	bool fini = true;
	for (int j = lhyf; j <= hn-rhyf; j++)
		if (hyf[j]%2)
			fini = false; 
	if (fini)
		return;
	auto q = hb->link, r = ha->link;
	ha->link = hb->link = nullptr;
	auto bchar = hyfbchar;
	LinkedNode *s; 
	int j = 0;
	if (ha->is_char_node())
	{
		initlig = false;
		auto Ha = dynamic_cast<CharNode*>(ha);
		if (Ha->font != hf)
		{
			s = ha;
			hu[0] = non_char;
			initlist = nullptr;
		}
		else
		{
			initlist = Ha;
			hu[0] = Ha->character;
			s = curp;
			followUntilBeforeTarget(s, ha);
		}
	}
	else 
		if (ha->type == ligature_node)
		{
			auto Ha = dynamic_cast<LigatureNode*>(ha);
			initlig = Ha->font == hf;
			if (initlig)
			{
				initlist = Ha->lig_ptr;
				initlft = Ha->subtype > 1;
				hu[0] = Ha->character;
				if (initlist == nullptr && initlft)
				{
					hu[0] = non_char;
					initlig = false;
				}
				s = curp;
				followUntilBeforeTarget(s, ha);
				delete ha;
			}
			else
			{
				s = ha;
				hu[0] = non_char;
				initlist = nullptr;
			}
		}
		else //kern ?
		{
			initlist = nullptr;
			s = ha;
			if (!ha->link->is_char_node() && ha->link->type == ligature_node && dynamic_cast<LigatureNode*>(ha->link)->subtype > 1)
			{
				hu[0] = 256;
				initlig = false;
			}
			else
				j = 1;
		}
	flushnodelist(r);
	do
	{
		int l = j;
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
				int i = hyphenpassed;
				hyf[i] = 0;
				LinkedNode *minortail = nullptr;
				dynamic_cast<DiscNode*>(r)->pre_break = nullptr;
				auto hyfnode = newcharacter(hf, hyfchar);
				ASCIIcode c;
				if (hyfnode)
				{
					i++;
					c = hu[i];
					hu[i] = hyfchar;
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
					delete hyfnode;
					hu[i] = c;
					l = i;
					i--;
				}
				minortail = 0;
				dynamic_cast<DiscNode*>(r)->pre_break = nullptr;
				int cloc = 0;
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
				if (rcount > 127) //we have to forget the discretionary hyphen
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

//! initializes the hyphenation pattern data
void newpatterns(Token t)
{
	if (!trienotready)
	{
		error("Too late for "+esc("patterns"), "All patterns must be given before typesetting begins.");
		scantoks(false, false, t);
		flushnodelist(defref);
		return;
	}
	//Enter all of the patterns into a linked tr, until coming to a right brace
	curlang = cur_fam();
	if (curlang <= 0 || curlang > 255)
			curlang = 0;
	t = scanleftbrace(); //a left brace must follow \\patterns
	hyf[0] = 0;
	std::string pattern;
	for (bool keepIn = true, digitsensed /*should the next digit be treated as a letter?*/ = false; keepIn;)
	{
		t = getxtoken();
		switch (t.cmd)
		{
			case letter:
			case other_char: //Append a new letter or a hyphen level
				if (!digitsensed && t.chr >= '0' || t.chr <= '9')
				{
					if (pattern.size() >= 63)
						break;
					hyf[pattern.size()] = t.chr-'0';
					digitsensed = true;
				}
				else
				{
					if (t.chr != '.' && lc_code(t.chr) == 0)
						error("Nonletter", "(See Appendix H.)");
					if (pattern.size() >= 63)
						break;
					t.chr = lc_code(t.chr);
					pattern += char(t.chr);
					hyf[pattern.size()] = 0;
					digitsensed = false;
				}
				break;
			case spacer:
			case right_brace:
				if (pattern != "") //Insert a new pattern into the linked tr
				{
					//Compute the tr op code, |v|, and set |l:=0|
					if (pattern[0] == '\0') // '.' = début de mot
						hyf[0] = 0;
					if (pattern.back() == '\0') // '.' = fin de mot
						hyf[pattern.size()] = 0;
					quarterword hyfNext = 0; //tr op code
					for (int l = pattern.size(); l >= 0; l--)
						if (hyf[l])
						{
							TrieOp to(pattern.size()-l/*hyfDistance*/, hyf[l]/*hyfNum*/, hyfNext, curlang);
							int l = tOpMap[to]; 
							if (l == 0)
							{
								to.val = ++trieused[curlang];
								trieOp.push_back(to);
								l = tOpMap[to] = trieOp.size()-1;
							}
							hyfNext = trieOp[l].val;
						}
					savePattern(pattern, hyfNext);
				}
				if (t.cmd == right_brace)
				{
					keepIn = false;
					continue;
				}
				pattern = "";
				hyf[0] = 0;
				digitsensed = false;
				break;
			default:
				error("Bad "+esc("patterns"), "(See Appendix H.)");
		}
	}
}

void newhyphexceptions(void)
{
	auto t = scanleftbrace();
	curlang = cur_fam();
	if (curlang < 0 || curlang > 255)
		curlang = 0;
	HyphenNode *p = nullptr;
	std::string exception;
	for (t = getxtoken(); true; t = getxtoken())
		switch (t.cmd)
		{
			case char_num:
				t.chr = scancharnum(); [[fallthrough]];
			case letter:
			case other_char:
			case char_given:
				if (t.chr == '-')
				{
					if (exception.size() >= 63)
						break;
					auto q = new HyphenNode(exception.size());
					appendAtStart(p, q); // p = q -> old p
				}
				else 
					if (lc_code(t.chr) == 0)
						error("Not a letter", "Letters in \\hyphenation words must have \\lccode>0.\nProceed; I'll ignore the character I just read.");
					else 
						if (exception.size() < 63)
							exception += char(lc_code(t.chr));
				break;
			case spacer:
			case right_brace:
				if (exception.size() > 1)
				{
					exception += char(curlang);
					exceptionList[exception] = p;
				}
				if (t.cmd == right_brace)
					return;
				p = nullptr;
				break;
			default:
				error("Improper "+esc("hyphenation")+" will be flushed", "Hyphenation exceptions must contain only letters\nand hyphens. But continue; I'll forgive and forget.");
		}
}
