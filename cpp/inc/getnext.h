#ifndef GETNEXT_H
#define GETNEXT_H

#include "globals.h"

enum scanner_status
{
	skipping = 1, //!< \a scanner_status when passing conditional text
	defining = 2, //!< \a scanner_status when reading a macro definition
	matching = 3, //!< \a scanner_status when reading macro arguments
	aligning = 4, //!< \a scanner_status when reading an alignment preamble
	absorbing = 5 //!< \a scanner_status when reading a balanced text
};

inline char scannerstatus = normal; // 0..5
inline halfword warningindex = 0;
inline bool forceeof = false;
inline int skipline;

[[nodiscard]] Token getnext(bool = true);

#endif
