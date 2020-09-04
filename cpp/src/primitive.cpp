#include "primitive.h"
#include "chaine.h"
#include "equivalent.h"

std::map<quarterword, std::map<halfword, std::string>> primName;

int primitive(ASCIIcode s, quarterword c, halfword o) 
{
	primName[c][o] = std::string(1, s);
	int val = s+single_base;
	eqtb_active[val-active_base].level = level_one;
	eqtb_active[val-active_base].type = c;
	eqtb_active[val-active_base].int_ = o; //MemoryWord*
	return val;
}

int primitive(const std::string &t, quarterword c, halfword o)
{
	primName[c][o] = t;
	int val = idlookup(t, false);
	flush_string();
	eqtb_cs[val-hash_base].text = t;
	eqtb_cs[val-hash_base].level = level_one;
	eqtb_cs[val-hash_base].type = c;
	eqtb_cs[val-hash_base].int_ = o; //MemoryWord*
	return val;
}
