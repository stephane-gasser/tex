#include "fixdateandtime.h"
#include "constantes.h"

void fixdateandtime(void)
{
	int_par(time_code) = 12 * 60;
	int_par(day_code) = 4;
	int_par(month_code) = 7;
	int_par(year_code) = 1776;
}
