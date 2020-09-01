#ifndef IDLOOKUP_H
#define IDLOOKUP_H

#include "globals.h"
#include "equivalent.h"

halfword idlookup(const std::string &);

inline halfword hashused = frozen_control_sequence;
inline std::vector<twohalves> hash(2881, {0, 0}); // débute à 514

#endif
