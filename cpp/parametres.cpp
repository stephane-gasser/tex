#include "tex.h"
#include "globals.h"
#include "parametres.h"

int& int_par(halfword p) { return eqtb[int_base+p].int_; }
halfword& glue_par(halfword p) { return equiv(glue_base+p); }
int& dimen_par(halfword p) { return eqtb[dimen_base+p].int_; }

