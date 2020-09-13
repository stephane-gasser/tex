#ifndef CESURE_H
#define CESURE_H

#include "globals.h"
#include "noeud.h"
#include "equivalent.h"

constexpr int hyph_size = 307; //!<  another prime; the number of \\hyphenation exceptions

typedef int hyphpointer; //0..307

class HyphenNode : public LinkedNode
{
	public:
		int pos;
		HyphenNode(int n) : pos(n) {}
};

inline int hyfchar;
inline halfword hyfbchar;
inline int lhyf, rhyf, initlhyf, initrhyf;
inline std::map<ASCIIcode, quarterword> trieused;
inline bool ligaturepresent = false; //!< should a ligature node be made for |cur_l|?
inline int hc[66]; // word to be hyphenated // of 0..256
inline int hu[64]; //like |hc|, before conversion to lowercase // of 0..256
inline smallnumber hn; //the number of positions occupied in |hc|
inline LinkedNode *ha, *hb; //nodes |ha..hb| should be replaced by the hyphenated result
inline internalfontnumber hf; //font number of the letters in |hc|
inline std::map<ASCIIcode, int> opstart; //of 0..trieopsize
inline bool trienotready = true;
inline halfword bchar;
inline ASCIIcode curlang;

inline void set_cur_lang(void) { curlang = (language() <= 0 || language() > 255) ? 0 : language(); }

void inittrie(void);
void hyphenate(LinkedNode*);
void newpatterns(Token);
void newhyphexceptions(void);

#endif
