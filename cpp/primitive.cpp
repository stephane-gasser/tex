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
	strnumber s = txt(t);
	t.copy(reinterpret_cast<char *>(buffer), bufsize+1);
	curval = idlookup(0, t.size());
	strptr--;
	poolptr = strstart[strptr];
	text(curval) = s;
	eq_level(curval) = level_one;
	eq_type(curval) = c;
	equiv(curval) = o;
}
