#ifndef IMPRESSION
#define IMPRESSION

#include "globals.h"
#include <string>

std::string cmdchr(Token);
std::string esc(const std::string &);
std::string asScaled(scaled);
std::string cs(int);
std::string scs(halfword);
std::string asSpec(GlueSpec*, const std::string &);
std::string asMode(int);
std::string asFilename(const std::string &, const std::string &, const std::string &);
std::string shortdisplay(int);
std::string tokenlist(TokenNode*, TokenNode*, int);
std::string tokenshow(TokenNode*);
std::string meaning(Token);
std::string romanint(int);
std::string twoDigits(int);
[[deprecated]] std::string showbox(halfword);
std::string showbox(BoxNode*);
std::string showcontext(void);
void diagnostic(const std::string &);
void print(const std::string &);
void println(void);
void printnl(const std::string &);
void print_err(const std::string &);
void slowprint(int);
void slowprint(const std::string &);
void showcurcmdchr(Token);
void showwhatever(Token);

#endif
