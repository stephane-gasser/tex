#include "primitive.h"
#include "idlookup.h"
#include "texte.h"

std::map<quarterword, std::map<halfword, std::string>> primName;

int primitive(ASCIIcode s, quarterword c, halfword o) 
{
	primName[c][o] = std::string(1, s);
	int val = s+single_base;
	eq_level(val) = level_one;
	eq_type(val) = c;
	equiv(val) = o;
	return val;
}

int primitive(const std::string &t, quarterword c, halfword o)
{
	primName[c][o] = t;
	int val = idlookup(t);
	flush_string();
	text(val) = txt(t);
	eq_level(val) = level_one;
	eq_type(val) = c;
	equiv(val) = o;
	return val;
}
