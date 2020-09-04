#ifndef FETCH_H
#define FETCH_H

#include "globals.h"
#include "noeud.h"
#include "police.h"

[[nodiscard]] std::tuple<Font, quarterword> fetch(NoadContent&);

#endif
