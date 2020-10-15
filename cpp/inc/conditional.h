#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "globals.h"
#include "token.h"
#include "noeud.h"

enum
{
	if_char_code = 0, //!<  `\\if' 
	if_cat_code = 1, //!<  `\\ifcat' 
	if_int_code = 2, //!<  `\\ifnum' 
	if_dim_code = 3, //!<  `\\ifdim' 
	if_odd_code = 4, //!<  `\\ifodd' 
	if_vmode_code = 5, //!<  `\\ifvmode' 
	if_hmode_code = 6, //!<  `\\ifhmode' 
	if_mmode_code = 7, //!<  `\\ifmmode' 
	if_inner_code = 8, //!<  `\\ifinner' 
	if_void_code = 9, //!<  `\\ifvoid' 
	if_hbox_code = 10, //!<  `\\ifhbox' 
	if_vbox_code = 11, //!<  `\\ifvbox' 
	ifx_code = 12, //!<  `\\ifx' 
	if_eof_code = 13, //!<  `\\ifeof' 
	if_true_code = 14, //!<  `\\iftrue' 
	if_false_code = 15, //!<  `\\iffalse' 
	if_case_code = 16 //!<  `\\ifcase' 
};

enum if_codes
{
	if_code = 1, //code for \if... being evaluated
	fi_code = 2, //code for \fi
	else_code = 3, //code for \else
	or_code = 4, //code for \or
};

void conditional(char, Token);

inline char iflimit = 0; // 0..4

class ConditionalNode : public LinkedNode
{
	public:
		quarterword subtype;
		int if_line_field;
		ConditionalNode(quarterword s) : subtype(s) { type = iflimit; }
};

inline ConditionalNode *condptr = nullptr;
inline int ifline = 0;
inline smallnumber curif = 0;

#endif
