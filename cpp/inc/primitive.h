#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "globals.h"
#include <map>

extern std::map<quarterword, std::map<halfword, std::string>> primName;

int primitive(ASCIIcode, quarterword, halfword);
int primitive(const std::string &, quarterword, halfword);

#endif
