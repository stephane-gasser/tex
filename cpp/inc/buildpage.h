#ifndef BUILDPAGE_H
#define BUILDPAGE_H

#include "globals.h"

inline scaled pagesofar[8];
inline auto &page_goal = pagesofar[0]; //!< desired height of information on page being built
inline auto &page_total = pagesofar[1]; //!< height of the current page
inline auto &page_shrink = pagesofar[6]; //!< shrinkability of the current page
inline auto &page_depth = pagesofar[7]; //!< depth of the current page
inline scaled pagemaxdepth = 0;
inline scaled bestsize;
inline char pagecontents = 0; // 0..2

void buildpage(void);

#endif
