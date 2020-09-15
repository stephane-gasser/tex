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

static void savePattern(const std::basic_string<halfword> &pattern, unsigned char *hyf)
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

static unsigned char hyf[65]; // of 0..9 //odd values indicate discretionary hyphens
static bool lfthit = false, rthit = false; //!< did we hit a ligature with a boundary character?

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

static smallnumber reconstitute(smallnumber j, smallnumber n, halfword bchar, halfword hchar, const std::basic_string<halfword> &word)
{
	hyphenpassed = 0;
	hold_head->link = nullptr;
	curl = word[j];
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
	halfword currh; // hyphen character for ligature testing
	curr = j < n ? word[j+1] : bchar;
	currh = hyf[j]%2 ? hchar : non_char;
	bool skipLoop;
	bool recommence;
	scaled w = 0;
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
		halfword testchar; // hyphen or other character for ligature testing
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
									ligstack->character = curr;
								else
								{
									auto l = new LigatureNode(curr);
									if (j == n)
										bchar = non_char;
									else
										l->lig_ptr = new CharNode(hf, word[j+1]);
									ligstack = l;
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
									{
										curr = j < n ? word[j+1] : bchar;
										currh = hyf[j]%2 ? hchar : non_char;
									}
									else
										curr = ligstack->character;
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
										curr = j < n ? word[j+1] : bchar;
										currh = hyf[j]%2 ? hchar : non_char;
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
			if (Font::skip_byte(k) >= stop_flag)
				if (currh == non_char)
				{
					skipLoop = true;
					continue;
				}
				else
				{
					currh = non_char;
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
			curl = ligstack->character;
			ligaturepresent = true;
			pop_lig_stack(j, t);
			auto p = ligstack;
			next(ligstack);
			delete p;
			if (ligstack == nullptr)
			{
				curr = j < n ? word[j+1] : bchar;
				currh = hyf[j]%2 ? hchar : non_char;
			}
			else
				curr = ligstack->character;
			recommence = true;
			continue;
		}
	} while (recommence);
	return j;
}

static std::map<quarterword, std::map<std::basic_string<halfword>, HyphenNode*>> exceptionList;

void hyphenate(LinkedNode *curp, std::basic_string<halfword> word)
{
	std::fill_n(hyf, word.size()+1, 0);
	//Look for the word |hc[1..hn]| in the exception table, and |goto found| (with |hyf| containing the hyphens) if an entry is found
	std::basic_string<halfword> wordToHyphen; //word to be hyphenated // of 0..256
	for (auto c: word)
		wordToHyphen += lc_code(c);
	if (exceptionList.find(curlang) != exceptionList.end() && exceptionList[curlang].find(wordToHyphen) != exceptionList[curlang].end()) //found
		for (auto s = exceptionList[curlang][wordToHyphen]; s; next(s))
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
	std::fill_n(hyf+word.size()-rhyf+1, rhyf, 0);
	bool fini = true;
	for (int j = lhyf; j <= word.size()-rhyf; j++)
		if (hyf[j]%2) // impair : césure autorisée
			fini = false; 
	if (fini) // pas de césure
		return;
	auto q = hb->link, r = ha->link;
	ha->link = hb->link = nullptr;
	auto bchar = hyfbchar;
	LinkedNode *s = ha;
	int j = 0;
	initlist = nullptr;
	initlig = false;
	word = halfword(non_char)+word;
	if (ha->is_char_node())
	{
		if (auto Ha = dynamic_cast<CharNode*>(ha); Ha->font == hf)
		{
			initlist = Ha;
			word[0] = Ha->character;
			s = curp;
			followUntilBeforeTarget(s, ha); // curp -> ... -> s -> ha
		}
	}
	else
		if (ha->type == ligature_node)
		{
			if (auto Ha = dynamic_cast<LigatureNode*>(ha); Ha->font == hf)
			{
				initlist = Ha->lig_ptr;
				initlft = Ha->subtype > 1;
				initlig = initlist || !initlft;
				if (initlig)
					word[0] = Ha->character;
				s = curp;
				followUntilBeforeTarget(s, ha); // curp -> ... -> s -> ha
				delete ha;
			}
		}
		else //kern ?
		{
			if (!ha->link->is_char_node() && ha->link->type == ligature_node && dynamic_cast<LigatureNode*>(ha->link)->subtype > 1)
				word[0] = non_char;
			else
				j = 1;
		}
	flushnodelist(r);
	while (j <= word.size())
	{
		int l = j;
		j = reconstitute(j, word.size(), bchar, hyfchar, word)+1;
		if (hyphenpassed == 0)
		{
			s->link = hold_head->link;
			followUntilBeforeTarget(s); // hold->head -> ... -> s -> null
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
				auto rcount = 0;
				LinkedNode *majortail;
				for (auto majortail = r; majortail->link; next(majortail)) //advance_major_tail
					rcount++;
				int i = hyphenpassed;
				hyf[i] = 0;
				LinkedNode *minortail = nullptr;
				dynamic_cast<DiscNode*>(r)->pre_break = nullptr;
				auto hyfnode = newcharacter(hf, hyfchar);
				ASCIIcode c;
				if (hyfnode)
				{
					i++;
					c = word[i];
					word[i] = hyfchar;
				}
				while (l <= i)
				{
					l = reconstitute(l, i, fonts[hf].bchar, non_char, word)+1;
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
					word[i] = c;
					l = i;
					i--;
				}
				minortail = 0;
				dynamic_cast<DiscNode*>(r)->pre_break = nullptr;
				int cloc = 0;
				if (fonts[hf].bcharlabel)
				{
					l--;
					c = word[l];
					cloc = l;
					word[l] = non_char;
				}
				while (l < j)
				{
					do
					{
						l = reconstitute(l, word.size(), bchar, non_char, word)+1;
						if (cloc > 0)
						{
							word[cloc] = c;
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
						j = reconstitute(j, word.size(), bchar, non_char, word)+1;
						for (majortail = hold_head; majortail->link; next(majortail)) //advance_major_tail
							rcount++;
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
	}
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
	std::basic_string<halfword> pattern;
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
				if (pattern.size()) //Insert a new pattern into the linked tr
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
				pattern = std::basic_string<halfword>();
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
	std::basic_string<halfword> exception;
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
					exceptionList[curlang][exception] = p;
				if (t.cmd == right_brace)
					return;
				p = nullptr;
				break;
			default:
				error("Improper "+esc("hyphenation")+" will be flushed", "Hyphenation exceptions must contain only letters\nand hyphens. But continue; I'll forgive and forget.");
		}
}
