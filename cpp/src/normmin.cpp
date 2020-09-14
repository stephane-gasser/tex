#include "normmin.h"

smallnumber normmin(int h)
{
	return std::max(1, std::min(63, h));
}
