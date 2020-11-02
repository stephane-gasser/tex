#ifndef CESURE_H
#define CESURE_H

#include "globals.h"
#include "token.h"
#include "noeud.h"
#include "equivalent.h"
#include <map>

constexpr int hyph_size = 307; //!<  another prime; the number of \\hyphenation exceptions

enum ligatures
{
	AB_C = 0, // symbole != ou LIG
	AB_CB = 1, //symbole =:| ou LIG/
	AB_cB = 5, //symbole =:|> ou LIG/>
	AB_AC = 2, //symbole |=: ou /LIG
	AB_aC = 6, //symbole |=:> ou /LIG>
	AB_ACB = 3, // symbole |=:| ou /LIG/
	AB_aCB = 7, //symbole |=:|> ou /LIG/>
	AB_acB = 11 //symbole |=:|>> ou /LIG/>>
};

typedef int hyphpointer; //0..307

class HyphenNode : public LinkedNode
{
	public:
		int pos;
		HyphenNode(int n) : pos(n) {}
};

inline int hyfchar;
inline halfword hyfbchar;
inline int lhyf, rhyf, initlhyf, initrhyf; //limits on fragment sizes
inline std::map<ASCIIcode, quarterword> trieused;
inline bool ligaturepresent = false; //!< should a ligature node be made for |cur_l|?
/*inline int hc[66]; // word to be hyphenated // of 0..256
inline int hu[64]; //like |hc|, before conversion to lowercase // of 0..256
inline smallnumber hn; //the number of positions occupied in |hc|*/
inline LinkedNode *ha, *hb; //nodes |ha..hb| should be replaced by the hyphenated result
inline internalfontnumber hf; //font number of the letters in |hc|
inline std::map<ASCIIcode, int> opstart; //of 0..trieopsize
inline bool trienotready = true;
inline halfword bchar;
inline ASCIIcode curlang;

inline void set_cur_lang(void) { curlang = (language() <= 0 || language() > 255) ? 0 : language(); }

void inittrie(void);
void hyphenate(LinkedNode*, std::basic_string<halfword>);
void newpatterns(char&, Token);
void newhyphexceptions(char);

#endif
