#include "primitive.h"
#include "idlookup.h"

void primitive(strnumber s, quarterword c, halfword o)
{
	if (s < 256)
		curval = s + 257;
	else
	{
		int k = strstart[s];
		int l = strstart[s+1]-k;
		for (int j = 0; j < l; j++)
			buffer[j] = strpool[k+j];
		curval = idlookup(0, l);
		strptr--;
		poolptr = strstart[strptr];
		hash[curval].rh = s;
	}
	eqtb[curval].hh.b1 = 1;
	eqtb[curval].hh.b0 = c;
	eqtb[curval].hh.rh = o;
}
