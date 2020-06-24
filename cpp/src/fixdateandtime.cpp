#include "fixdateandtime.h"

void fixdateandtime(void)
{
	time() = 12 * 60;
	day() = 4;
	month() = 7;
	year() = 1776;
}
