#include "tokenshow.h"
#include "showtokenlist.h"

void tokenshow(halfword p)
{
	if (p)
		showtokenlist(link(p), 0, 10000000);
}
