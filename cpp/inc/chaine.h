#ifndef CHAINE_H
#define CHAINE_H

#include "globals.h"
#include "equivalent.h"

constexpr int hash_prime = 1777; //!<  a prime number equal to about 85% of \a hash_size

inline std::vector<std::string> strings;
inline std::string currentString;
inline halfword hashused = frozen_control_sequence;
inline std::vector<twohalves> hash(2881, {0, 0}); // débute à 514

halfword idlookup(const std::string &, bool = true);
int cur_length(void);
void append_char(ASCIIcode);
bool getstringsstarted(void);

#endif
