#ifndef LECTURE_H
#define LECTURE_H

#include "globals.h"
#include "token.h"
#include "noeud.h"

enum token_type
{
	parameter = 0, //!< \a token_type code for parameter
	u_template = 1, //!< \a token_type code for \f$<u_j>\f$ template
	v_template = 2, //!< \a token_type code for \f$<v_j>\f$ template
	backed_up = 3, //!< \a token_type code for text to be reread
	inserted = 4, //!< \a token_type code for inserted texts
	macro = 5, //!< \a token_type code for defined control sequences
	output_text = 6, //!< \a token_type code for output routines
	every_par_text = 7, //!< \a token_type code for \\everypar
	every_math_text = 8, //!< \a token_type code for \\everymath
	every_display_text = 9, //!< \a token_type code for \\everydisplay
	every_hbox_text = 10, //!< \a token_type code for \\everyhbox
	every_vbox_text = 11, //!< \a token_type code for \\everyvbox
	every_job_text = 12, //!< \a token_type code for \\everyjob
	every_cr_text = 13, //!< \a token_type code for \\everycr
	mark_text = 14, //!< \a token_type code for \\topmark, etc.
	write_text = 15 //!< \a token_type code for \\write
};

inline smallnumber radix = 0;
inline glueord curorder = 0;

[[nodiscard]] int scanint(char);
[[nodiscard]] int scancharnum(char);
[[nodiscard]] int scantwentysevenbitint(char);
[[nodiscard]] int scaneightbitint(char);
[[nodiscard]] int scanfifteenbitint(char);
[[nodiscard]] int scanfourbitint(char);
[[nodiscard]] int scandimen(char, bool, bool, bool);
[[nodiscard]] int scan_normal_dimen(char);
[[nodiscard]] int scanfontident(void);
[[nodiscard]] GlueSpec *scanglue(char, smallnumber);
[[nodiscard]] TokenList* readtoks(int, halfword);
[[nodiscard]] Token getxtoken(void);
[[nodiscard]] Token xtoken(Token);
[[nodiscard]] halfword getrtoken(void);
void scanbox(int);
bool scankeyword(const std::string &);
[[nodiscard]] Token scanleftbrace(void);
void scanmath(NoadContent&);
void scanoptionalequals(void);
RuleNode *scanrulespec(Token);
[[nodiscard]] Token scanspec(groupcode);
[[nodiscard]] Token scanspec(groupcode, int);
void convtoks(Token);
void beginTokenListBelowMacro(TokenList*, quarterword);
void beginTokenListMacro(TokenList*);
void beginTokenListAboveMacro(TokenList*, quarterword);
void endtokenlist(void);
Token getpreambletoken(void);
void insthetoks(void);
void thetoks(TokenList&);
Token getXTokenSkipSpace(void);
Token getXTokenSkipSpaceAndEscape(void);

inline void back_list(TokenList *p) { beginTokenListBelowMacro(p, backed_up); } //!< backs up a simple token list
inline void ins_list(TokenList *p) { beginTokenListBelowMacro(p, inserted); } //!< inserts a simple token list

#endif
