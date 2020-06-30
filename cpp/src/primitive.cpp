#include "primitive.h"
#include "idlookup.h"
#include "texte.h"

std::map<quarterword, std::map<halfword, std::string>> primName;

void primitive(ASCIIcode s, quarterword c, halfword o) 
{
	primName[c][o] = std::string(1, s);
	curval = s+single_base;
	eq_level(curval) = level_one;
	eq_type(curval) = c;
	equiv(curval) = o;
}

void primitive(const std::string &t, quarterword c, halfword o)
{
	primName[c][o] = t;
	curval = idlookup(t);
	flush_string();
	text(curval) = txt(t);
	eq_level(curval) = level_one;
	eq_type(curval) = c;
	equiv(curval) = o;
}
