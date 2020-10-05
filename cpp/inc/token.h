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
		Token(void) : cmd(0), chr(0), cs(0), tok(0) {}
		Token(halfword token) : tok(token)
		{
			if (tok > cs_token_flag)
			{
				cs = tok-cs_token_flag;
				cmd = 0;
				chr = 0;
			}
			else
			{
				cs = 0;
				cmd = tok>>8;
				chr = tok%8;
			}
		}
		Token(eightbits cm, halfword ch) : cmd(cm), chr(ch), cs(0), tok((cmd<<8)+chr) {}
		Token(const Token &t) : cs(t.cs), cmd(cs ? 0 : t.cmd), chr(cs ? 0 : t.chr), tok(cs ? cs+cs_token_flag : (cmd<<8)+chr) {}
};

void strtoks(const std::string &);

void scanMacroToks(bool, Token);
void scanNonMacroToks(Token);
void scanNonMacroToksExpand(Token);

class TokenList : public AnyNode
{
	public:
		std::vector<halfword> list;
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
inline TokenList holdHead; //!< head of a temporary list of another kind
inline TokenList tempHead; //!< head of a temporary list of some kind
inline TokenList Start;
inline halfword Loc;
inline std::vector<TokenList> paramstack;

void beginTokenListAboveMacro(TokenList *, quarterword);
std::string tokenlist(TokenList *, int);

#endif

