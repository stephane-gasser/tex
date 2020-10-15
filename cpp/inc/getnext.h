#ifndef GETNEXT_H
#define GETNEXT_H

#include "globals.h"
#include "token.h"

enum scanner_status
{
	skipping = 1, //!< \a scanner_status when passing conditional text
	defining = 2, //!< \a scanner_status when reading a macro definition
	matching = 3, //!< \a scanner_status when reading macro arguments
	aligning = 4, //!< \a scanner_status when reading an alignment preamble
	absorbing = 5 //!< \a scanner_status when reading a balanced text
};

class Scanner
{
};

[[nodiscard]] Token getnext(char, bool = true);
void passtext(void);

inline halfword warningindex = 0;
inline bool forceeof = false;
inline int skipline;

[[nodiscard]] inline Token gettoken(char status) { return getnext(status, false); }

#endif
