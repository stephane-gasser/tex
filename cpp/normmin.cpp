#include "normmin.h"

smallnumber normmin(int h)
{
	if (h <= 0)
		return 1;
	if (h >= 63)
		return 63;
	return h;
}
