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
[[nodiscard]] std::tuple<int, int> scansomethinginternal(smallnumber, bool);
[[nodiscard]] int scanglue(smallnumber);
void scanbox(int);
void scandelimiter(halfword, bool);
void scanfilename(void);
bool scankeyword(const std::string &);
void scanleftbrace(void);
void scanmath(halfword);
void scanoptionalequals(void);
halfword scanrulespec(void);
void scanspec(groupcode, bool);
halfword scantoks(bool, bool);
void convtoks(void);
void back_list(halfword);
void ins_list(halfword);
void begintokenlist(halfword, quarterword);
void deletetokenref(halfword);
void endtokenlist(void);
void getpreambletoken(void);
void getrtoken(void);
void gettoken(void);
void getxtoken(void);
void insthetoks(void);
[[nodiscard]] int readtoks(int, halfword);
halfword thetoks(void);
void xtoken(void);

#endif
