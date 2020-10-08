#ifndef IMPRESSION
#define IMPRESSION

#include "globals.h"
#include "noeud.h"
#include "token.h"
#include <string>
#include <map>

inline char termoffset = 0; // 0..maxprintline
inline char fileoffset = 0; // 0..maxprintline
inline std::map<ASCIIcode, char> xchr;

std::string cmdchr(Token);
std::string esc(const std::string &);
std::string asScaled(scaled);
std::string cs(int);
std::string scs(halfword);
std::string asSpec(GlueSpec*, const std::string &);
std::string asMode(int);
std::string asFilename(const std::string &, const std::string &, const std::string &);
std::string shortdisplay(LinkedNode *);
std::string tokenshow(TokenList *);
std::string meaning(Token);
std::string twoDigits(int);
std::string showbox(BoxNode*);
std::string showcontext(void);
void diagnostic(const std::string &);
void print(const std::string &);
void println(void);
void print_err(const std::string &);
void showcurcmdchr(Token);
void showwhatever(Token);

#endif
