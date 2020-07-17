#ifndef LECTURE_H
#define LECTURE_H

#include "globals.h"
#include <tuple>

[[nodiscard]] int scanint(halfword);
[[nodiscard]] int scancharnum(halfword);
[[nodiscard]] int scantwentysevenbitint(halfword);
[[nodiscard]] int scaneightbitint(halfword);
[[nodiscard]] int scanfifteenbitint(halfword);
[[nodiscard]] int scanfourbitint(halfword);
[[nodiscard]] int scandimen(bool, bool, bool, halfword);
[[nodiscard]] int scan_normal_dimen(halfword);
[[nodiscard]] int scanfontident(halfword);
[[nodiscard]] std::tuple<int, int> scansomethinginternal(smallnumber, bool, eightbits, halfword, halfword, halfword);
[[nodiscard]] int scanglue(smallnumber, halfword);
[[nodiscard]] int readtoks(int, halfword, halfword);
[[nodiscard]] std::tuple<eightbits, halfword, halfword, halfword> gettoken(halfword);
[[nodiscard]] std::tuple<eightbits, halfword, halfword, halfword> getxtoken(halfword);
[[nodiscard]] std::tuple<eightbits, halfword, halfword> xtoken(eightbits, halfword, halfword, halfword);
[[nodiscard]] halfword getrtoken(halfword);
void scanbox(int, halfword);
void scandelimiter(halfword, bool, halfword, halfword);
void scanfilename(halfword);
bool scankeyword(const std::string &, halfword);
[[nodiscard]] std::tuple<eightbits, halfword, halfword> scanleftbrace(halfword);
void scanmath(halfword, halfword);
void scanoptionalequals(halfword);
halfword scanrulespec(eightbits, halfword);
[[nodiscard]] std::tuple<eightbits, halfword, halfword> scanspec(groupcode, bool, halfword);
halfword scantoks(bool, bool, halfword, halfword);
void convtoks(halfword, halfword);
void back_list(halfword);
void ins_list(halfword);
void begintokenlist(halfword, quarterword);
void deletetokenref(halfword);
void endtokenlist(halfword);
std::tuple<eightbits, halfword> getpreambletoken(halfword);
void insthetoks(halfword);
halfword thetoks(halfword);

#endif
