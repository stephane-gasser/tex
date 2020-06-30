#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "globals.h"
#include <map>

extern std::map<quarterword, std::map<halfword, std::string>> primName;

void primitive(ASCIIcode, quarterword, halfword);
void primitive(const std::string &, quarterword, halfword);

#endif
