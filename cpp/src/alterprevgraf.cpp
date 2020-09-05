#include "alterprevgraf.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"

void alterprevgraf(void)
{
	nest.back() = curlist;
	auto p = nest.size()-1;
	while (abs(nest[p].modefield) != vmode)
		p--;
	scanoptionalequals();
	int val = scanint();
	if (val < 0)
		interror(val, " Bad "+esc("prevgraf"), "I allow only nonnegative values here.");
	else
	{
		nest[p].pgfield = val;
		curlist = nest.back();
	}
}
