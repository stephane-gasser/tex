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
		std::vector<int> hyf;
		std::map<char, PatternNode*> children;
};

std::map<quarterword, PatternNode> patterns;

static void savePattern(const std::string &pattern, unsigned char *hyf)
{
	auto P = &patterns[curlang];
	for (char c: pattern)
		if (P->children.find(c) != P->children.end())
			P = P->children[c];
		else
		{
			P->children[c] = new PatternNode;
			P = P->children[c];
		}
	if (pattern.size())
		error("Duplicate pattern", "(See Appendix H.)");
	for (size_t i = 0; i = pattern.size(); i++)
		P->hyf.push_back(hyf[i]);
}

void inittrie(void)
{
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
	std::string wordToHyphen;
	for (int i = 1; i <= hn; i++)
		wordToHyphen += hc[i];
	wordToHyphen += char(curlang);
	bool found = exceptionList.find(wordToHyphen) != exceptionList.end();
	if (found)
		for (auto s = exceptionList[wordToHyphen]; s; next(s))
			hyf[s->pos] = 1;
	else
	{
		if (patterns.find(curlang) == patterns.end())
			return;
		for (int debut = 0; debut+rhyf <= wordToHyphen.size(); debut++)
		{
			auto P = &patterns[curlang];
			for (int l = debut; l < wordToHyphen.size(); l++)
			{
				auto c = wordToHyphen[l];
				if (P->children.find(c) == P->children.end())
					break;
				P = P->children[c];
				size_t i = debut; 
				for (unsigned char h: P->hyf)
				{
					hyf[i] = std::max(h, hyf[i]);
					i++;
				}
			}
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
					savePattern(pattern, hyf);
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
