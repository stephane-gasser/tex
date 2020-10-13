#ifndef BOITE_H
#define BOITE_H

#include "globals.h"
#include "token.h"
#include "noeud.h"

enum box_dim
{
	exactly = 0, //!< a box dimension is pre-specified
	additional = 1 //!< a box dimension is increased from the natural one
};

enum chr_code
{
	box_code = 0, //!< \a chr_code for `\\box'
	copy_code = 1, //!< \a chr_code for `\\copy'
	last_box_code = 2, //!< \a chr_code for `\\lastbox'
	vsplit_code = 3, //!< \a chr_code for `\\vsplit'
	vtop_code = 4 //!< \a chr_code for `\\vtop'
};

inline int lastbadness = 0;

BoxNode *rebox(BoxNode*, scaled);
BoxNode *cleanbox(NoadContent&, smallnumber);
void alterboxdimen(halfword);
void beginbox(int, Token);
void boxend(int, RuleNode*);
BoxNode *charbox(internalfontnumber, quarterword);
void ensurevbox(eightbits);
BoxNode *vpackage(LinkedNode*, scaled, smallnumber, scaled);
BoxNode *vpack(LinkedNode*, scaled, smallnumber);
BoxNode *hpack(LinkedNode*, scaled, smallnumber);
void package(smallnumber, Token);
void unpackage(halfword);

#endif
