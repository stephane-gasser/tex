#ifndef IMPRESSION
#define IMPRESSION

#include "globals.h"
#include <string>

std::string cmdchr(quarterword, halfword);
std::string esc(const std::string &);
std::string asScaled(scaled);
void print(const std::string &);
void print_err(const std::string &);
std::string cs(int);
std::string scs(halfword);
void printcurrentstring(void);
void printdelimiter(halfword);
void printfamandchar(halfword);
void printfilename(const std::string &, const std::string &, const std::string &);
void printfontandchar(int);
void println(void);
void printmark(int);
void printmeaning(void);
void printmode(int);
void printnl(const std::string &);
void printromanint(int);
void printruledimen(scaled);
void printspec(int, const std::string &);
void printsubsidiarydata(halfword, ASCIIcode);
void printtwo(int);
void printwritewhatsit(const std::string &, halfword);
void slowprint(int);
void slowprint(const std::string &);
void showtokenlist(int, int, int);
void tokenshow(halfword);
void shortdisplay(int);
void showinfo(void);
void shownodelist(int);
void showbox(halfword);
void showcontext(void);
void begindiagnostic(void);
void enddiagnostic(bool);
void showcurcmdchr(void);
void showactivities(void);
void showwhatever(void);

#endif
