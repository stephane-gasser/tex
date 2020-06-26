#ifndef IMPRESSION
#define IMPRESSION

#include "globals.h"
#include <string>

void print(const std::string &);
void print_err(const std::string &);
void printchar(ASCIIcode);
void printcmdchr(quarterword, halfword);
void printcs(int);
void printcurrentstring(void);
void printdelimiter(halfword);
void printesc(const std::string &);
std::string esc(const std::string &);
void printfamandchar(halfword);
void printfilename(const std::string &, const std::string &, const std::string &);
void printfontandchar(int);
void printglue(scaled, int, const std::string &);
void printhex(int);
void printint(int);
void printlengthparam(int);
void println(void);
void printmark(int);
void printmeaning(void);
void printmode(int);
void printnl(const std::string &);
void printparam(int);
void printromanint(int);
void printruledimen(scaled);
void printscaled(scaled);
void printsize(int);
void printskipparam(int);
void printspec(int, const std::string &);
void printstyle(int);
void printsubsidiarydata(halfword, ASCIIcode);
void printthedigs(eightbits);
void printtotals(void);
void printtwo(int);
void printwritewhatsit(const std::string &, halfword);
void slowprint(int);
void slowprint(const std::string &);
void sprintcs(halfword);
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
