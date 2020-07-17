#ifndef GETNEXT_H
#define GETNEXT_H

#include "globals.h"
#include <tuple>

[[nodiscard]] std::tuple<eightbits, halfword, halfword> getnext(halfword);
#endif
