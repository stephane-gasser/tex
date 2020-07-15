#ifndef LECTURE_H
#define LECTURE_H

#include "globals.h"
#include <tuple>

[[nodiscard]] int scanint(void);
[[nodiscard]] int scancharnum(void);
[[nodiscard]] int scantwentysevenbitint(void);
[[nodiscard]] int scaneightbitint(void);
[[nodiscard]] int scanfifteenbitint(void);
[[nodiscard]] int scanfourbitint(void);
[[nodiscard]] int scandimen(bool, bool, bool);
[[nodiscard]] int scan_normal_dimen(void);
[[nodiscard]] int scanfontident(void);
[[nodiscard]] std::tuple<int, int> scansomethinginternal(smallnumber, bool, eightbits, halfword, halfword);
[[nodiscard]] int scanglue(smallnumber);
[[nodiscard]] int readtoks(int, halfword);
[[nodiscard]] std::tuple<eightbits, halfword, halfword, halfword> gettoken(void);
[[nodiscard]] std::tuple<eightbits, halfword, halfword, halfword> getxtoken(void);
[[nodiscard]] std::tuple<eightbits, halfword, halfword> xtoken(eightbits, halfword, halfword);
[[nodiscard]] halfword getrtoken(void);
void scanbox(int);
void scandelimiter(halfword, bool, halfword);
void scanfilename(void);
bool scankeyword(const std::string &);
[[nodiscard]] std::tuple<eightbits, halfword, halfword> scanleftbrace(void);
void scanmath(halfword);
void scanoptionalequals(void);
halfword scanrulespec(eightbits);
[[nodiscard]] std::tuple<eightbits, halfword, halfword> scanspec(groupcode, bool);
halfword scantoks(bool, bool, halfword);
void convtoks(halfword);
void back_list(halfword);
void ins_list(halfword);
void begintokenlist(halfword, quarterword);
void deletetokenref(halfword);
void endtokenlist(void);
std::tuple<eightbits, halfword> getpreambletoken(void);
void insthetoks(void);
halfword thetoks(void);

#endif
