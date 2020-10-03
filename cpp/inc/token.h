#ifndef TOKEN_H
#define TOKEN_H

#include "globals.h"

enum special_token
{
	out_param_token = out_param<<8, //!< \f$2^8\cdot\textrm{out_param}\f$
	math_shift_token = math_shift<<8, //!< \f$2^8\cdot\textrm{math_shift}\f$
	tab_token = tab_mark<<8, //!< \f$2^8\cdot\textrm{tab_mark}\f$
	space_token = (spacer<<8)+' ', //!< \f$2^8\cdot\textrm{spacer}+\textrm{" "}\f$
	left_brace_token = left_brace<<8, //!< \f$2^8\cdot\textrm{left_brace}\f$
	right_brace_token = right_brace<<8, //!< \f$2^8\cdot\textrm{right_brace}\f$
	other_token = other_char<<8, //!< \f$2^8\cdot\textrm{other_char}\f$
		zero_token = other_token+'0', //!< zero, the smallest digit
		octal_token = other_token+'\'', //!< apostrophe, indicates an octal constant
		hex_token = other_token+'\"', //!< double quote, indicates a hex constant
		alpha_token = other_token+'`', //!< reverse apostrophe, precedes alpha constants
		point_token = other_token+'.', //!< decimal point
		continental_point_token = other_token+',', //!< decimal point, Eurostyle
		other_A_token = other_token+'A', //!< special hex digit of type \a other_char
	right_brace_limit = (right_brace+1)<<8, //!< \f$2^8\cdot(\textrm{right_brace}+1)\f$
	left_brace_limit = (left_brace+1)<<8,  //!< \f$2^8\cdot(\textrm{left_brace}+1)\f$
	match_token = match<<8, //!< \f$2^8\cdot\textrm{match}\f$
	end_match_token = end_match<<8, //!< \f$2^8\cdot\textrm{end_match}\f$
	letter_token = letter<<8, //!< \f$2^8\cdot\textrm{letter}\f$
		A_token = letter_token+'A' //!< the smallest special hex digit
};

class Token
{
	public:
		eightbits cmd;
		halfword chr;
		halfword cs;
		halfword tok;
};

inline Token make_tok(Token t)
{
	t.tok = t.cs == 0 ? (t.cmd<<8)+t.chr : t.cs+cs_token_flag;
	return t;
}

inline Token make_tok(halfword tok)
{
	Token t;
	t.tok = tok;
	return t;
}

inline Token make_tok(eightbits cmd, halfword chr)
{
	Token t;
	t.cmd = cmd;
	t.chr = chr;
	return t;
}

class TokenNode2
{
	public:
		halfword token;
		TokenNode2(halfword t = 0) : token(t) {}
		TokenNode2* copy(void) { return new TokenNode2(token); }
};

void strtoks(const std::string &);

void scanMacroToks(bool, Token);
void scanNonMacroToks(Token);
void scanNonMacroToksExpand(Token);

class TokenList : public AnyNode
{
	public:
		std::vector<TokenNode2> list;
		halfword token_ref_count;
		void deleteTokenRef(void) 
		{
			if (token_ref_count)
				token_ref_count--;
			else
				list.clear();
		}
};

inline TokenList defRef;
inline TokenList holdHead;

void beginTokenListAboveMacro(TokenList *, quarterword);
std::string tokenlist(TokenList *, TokenNode2 *, int);

#endif

