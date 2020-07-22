#ifndef CESURE_H
#define CESURE_H

#include "globals.h"

void inittrie(void);
quarterword newtrieop(smallnumber, smallnumber, quarterword);
void hyphenate(void);
void newpatterns(Token);

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

inline std::vector<TrieNode> trieNode(1);
inline triepointer &trie_root = trieNode[0].l; //!< root of the linked trie

class Trie
{
	public:
		bool taken;
		twohalves hh;
};

inline std::vector<Trie> trie(1);

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

inline std::vector<TrieOp> trieOp(1);

#endif
