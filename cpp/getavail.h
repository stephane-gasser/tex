#ifndef GETAVAIL_H
#define GETAVAIL_H

#include "globals.h"

halfword getavail(void);
halfword fast_get_avail(void);
void store_new_token(halfword &, halfword);
void fast_store_new_token(halfword &, halfword);
void free_avail(halfword);

#endif
