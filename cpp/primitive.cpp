#include "primitive.h"
#include "idlookup.h"
#include "texte.h"

void primitive(ASCIIcode s, quarterword c, halfword o) 
{
	curval = s+single_base;
	eq_level(curval) = level_one;
	eq_type(curval) = c;
	equiv(curval) = o;
}

void primitive(const std::string &t, quarterword c, halfword o) 
{
	curval = idlookup(t);
	flush_string();
	text(curval) = txt(t);
	eq_level(curval) = level_one;
	eq_type(curval) = c;
	equiv(curval) = o;
}
