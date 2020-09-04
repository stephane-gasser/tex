#ifndef BUILDPAGE_H
#define BUILDPAGE_H

#include "globals.h"
#include "noeud.h"

inline scaled pagesofar[8];
inline auto &page_goal = pagesofar[0]; //!< desired height of information on page being built
inline auto &page_total = pagesofar[1]; //!< height of the current page
inline auto &page_shrink = pagesofar[6]; //!< shrinkability of the current page
inline auto &page_depth = pagesofar[7]; //!< depth of the current page
inline scaled pagemaxdepth = 0;
inline scaled bestsize;
inline char pagecontents = 0; // 0..2
inline scaled lastkern = 0;
inline int lastpenalty = 0;
inline int deadcycles = 0;
inline int insertpenalties = 0;
inline LinkedNode *contrib_tail = nest[0].tailfield;

void buildpage(void);

#endif
