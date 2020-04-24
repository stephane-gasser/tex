#include "streqstr.h"

bool streqstr(strnumber s, strnumber t)
{
	if (strstart[s+1]-strstart[s] != strstart[t+1]-strstart[t])
		return false;
	for (auto j = strstart[s], k = strstart[t]; j < strstart[s+1]; j++, k++)
		if (strpool[j] != strpool[k])
			return false;
	return true;
}
