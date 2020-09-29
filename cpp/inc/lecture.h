#ifndef LECTURE_H
#define LECTURE_H

#include "globals.h"
#include "noeud.h"

inline smallnumber radix = 0;
inline glueord curorder = 0;
inline TokenNode * defref;

[[nodiscard]] int scanint(void);
[[nodiscard]] int scancharnum(void);
[[nodiscard]] int scantwentysevenbitint(void);
[[nodiscard]] int scaneightbitint(void);
[[nodiscard]] int scanfifteenbitint(void);
[[nodiscard]] int scanfourbitint(void);
[[nodiscard]] int scandimen(bool, bool, bool);
[[nodiscard]] int scan_normal_dimen(void);
[[nodiscard]] int scanfontident(void);
[[nodiscard]] GlueSpec *scanglue(smallnumber);
[[nodiscard]] TokenNode* readtoks(int, halfword);
[[nodiscard]] Token gettoken(void);
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
TokenNode* scantoks(bool, bool, Token);
void convtoks(Token);
void back_list(TokenNode*);
void ins_list(TokenNode*);
void begintokenlist(TokenNode*, quarterword);
void deletetokenref(TokenNode*);
void endtokenlist(void);
Token getpreambletoken(void);
void insthetoks(void);
TokenNode* thetoks(void);
Token getXTokenSkipSpace(void);
Token getXTokenSkipSpaceAndEscape(void);

#endif
