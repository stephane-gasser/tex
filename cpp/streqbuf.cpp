#include "streqbuf.h"

bool streqbuf(strnumber s, int k)
{
	for (auto j = strstart[s]; j < strstart[s+1]; j++, k++)
		if (strpool[j] != buffer[k])
			return false;
	return true;
}
