#include "primitive.h"
#include "idlookup.h"

void primitive(strnumber s, quarterword c, halfword o)
{
	if (s < 256)
		curval = s+257;
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
	eq_level(curval) = 1;
	eq_type(curval) = c;
	equiv(curval) = o;
}
