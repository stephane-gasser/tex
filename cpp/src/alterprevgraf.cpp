#include "alterprevgraf.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void alterprevgraf(void)
{
	nest[nestptr] = curlist;
	auto p = nestptr;
	while (abs(nest[p].modefield) != 1)
		p--;
	scanoptionalequals();
	curval = scanint();
	if (curval < 0)
		interror(curval, " Bad "+esc("prevgraf"), "I allow only nonnegative values here.");
	else
	{
		nest[p].pgfield = curval;
		curlist = nest[nestptr];
	}
}
