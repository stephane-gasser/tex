#ifndef IMPRESSION
#define IMPRESSION

#include "globals.h"
#include <string>

std::string cmdchr(quarterword, halfword);
std::string esc(const std::string &);
std::string asScaled(scaled);
std::string cs(int);
std::string scs(halfword);
std::string asSpec(int, const std::string &);
std::string asMode(int);
std::string asFilename(const std::string &, const std::string &, const std::string &);
std::string shortdisplay(int);
std::string tokenlist(int, int, int);
std::string tokenshow(halfword);
std::string meaning(void);
std::string romanint(int);
std::string twoDigits(int);
std::string showbox(halfword);
std::string showcontext(void);
std::string enddiagnostic(bool);
void print(const std::string &);
void println(void);
void printnl(const std::string &);
void print_err(const std::string &);
void slowprint(int);
void slowprint(const std::string &);
void begindiagnostic(void);
void showcurcmdchr(void);
void showwhatever(void);

#endif
