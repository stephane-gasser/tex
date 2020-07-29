#ifndef LECTURE_H
#define LECTURE_H

#include "globals.h"
#include <tuple>

inline TokenListNode * defref;

[[nodiscard]] int scanint(void);
[[nodiscard]] int scancharnum(void);
[[nodiscard]] int scantwentysevenbitint(void);
[[nodiscard]] int scaneightbitint(void);
[[nodiscard]] int scanfifteenbitint(void);
[[nodiscard]] int scanfourbitint(void);
[[nodiscard]] int scandimen(bool, bool, bool);
[[nodiscard]] int scan_normal_dimen(void);
[[nodiscard]] int scanfontident(void);
[[nodiscard]] std::tuple<int, int> scansomethinginternal(smallnumber, bool, Token);
[[nodiscard]] int scanglue(smallnumber);
[[nodiscard]] TokenListNode* readtoks(int, halfword);
[[nodiscard]] Token gettoken(void);
[[nodiscard]] Token getxtoken(void);
[[nodiscard]] Token xtoken(Token);
[[nodiscard]] halfword getrtoken(void);
void scanbox(int);
void scandelimiter(halfword, bool, Token);
void scanfilename(void);
bool scankeyword(const std::string &);
[[nodiscard]] Token scanleftbrace(void);
void scanmath(halfword);
void scanoptionalequals(void);
halfword scanrulespec(Token);
[[nodiscard]] Token scanspec(groupcode, bool);
TokenNode* scantoks(bool, bool, Token);
void convtoks(Token);
void back_list(halfword);
void ins_list(halfword);
void begintokenlist(halfword, quarterword);
void deletetokenref(halfword);
void endtokenlist(void);
Token getpreambletoken(void);
void insthetoks(void);
TokenNode* thetoks(void);
Token getXTokenSkipSpace(void);
Token getXTokenSkipSpaceAndEscape(void);

#endif
