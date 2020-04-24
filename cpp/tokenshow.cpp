#include "tokenshow.h"
#include "showtokenlist.h"

void tokenshow(halfword p)
{
  if (p)
	showtokenlist(mem[p].hh.rh, 0, 10000000);
}
