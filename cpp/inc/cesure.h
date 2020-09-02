#ifndef CESURE_H
#define CESURE_H

#include "globals.h"

constexpr int hyph_size = 307; //!<  another prime; the number of \\hyphenation exceptions

typedef int hyphpointer; //0..307

class TrieNode
{
	public:
		packedASCIIcode c;
		quarterword o;
		triepointer l;
		triepointer r;
		bool operator == (const TrieNode &tn) const { return std::tuple(c, o, l, r) == std::tuple(tn.c, tn.o, tn.l, tn.r); }
		bool operator < (const TrieNode &tn) const { return std::tuple(c, o, l, r) < std::tuple(tn.c, tn.o, tn.l, tn.r); }
};

class Trie
{
	public:
		bool taken;
		twohalves hh;
};

class TrieOp
{
	public:
		ASCIIcode lang;
		quarterword val;
		quarterword hyfnext;
		smallnumber hyfnum;
		smallnumber hyfdistance;
		bool operator == (const TrieOp &to) const { return std::tuple(lang, hyfnext, hyfnum, hyfdistance) == std::tuple(to.lang, to.hyfnext, to.hyfnum, to.hyfdistance); }
		bool operator < (const TrieOp &to) const { return std::tuple(lang, hyfnext, hyfnum, hyfdistance) < std::tuple(to.lang, to.hyfnext, to.hyfnum, to.hyfdistance); }
};

class HyphenNode : public LinkedNode
{
	public:
		int pos;
};

inline int hyfchar;
inline halfword hyfbchar;
inline int lhyf, rhyf, initlhyf, initrhyf;
inline std::map<ASCIIcode, quarterword> trieused;
inline bool ligaturepresent = false;
inline int hc[66]; // of 0..256
inline smallnumber hn;
inline LinkedNode *ha, *hb;
inline internalfontnumber hf;
inline int hu[64]; // of 0..256
inline LigatureNode *ligstack;
inline LinkedNode * curq;
inline std::map<ASCIIcode, int> opstart; //of 0..trieopsize
inline std::vector<TrieNode> trieNode(1);
inline triepointer &trie_root = trieNode[0].l; //!< root of the linked trie
inline std::vector<Trie> trie(1);
inline std::vector<TrieOp> trieOp(1);
inline std::vector<HyphenNode*> hyphlist(308, nullptr);
inline std::vector<std::string> hyphword(308, "");
inline hyphpointer hyphcount = 0;

void inittrie(void);
quarterword newtrieop(smallnumber, smallnumber, quarterword);
void hyphenate(LinkedNode*);
void newpatterns(Token);
void newhyphexceptions(void);

#endif
