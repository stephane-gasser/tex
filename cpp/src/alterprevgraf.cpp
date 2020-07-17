#include "alterprevgraf.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void alterprevgraf(halfword align)
{
	nest[nestptr] = curlist;
	auto p = nestptr;
	while (abs(nest[p].modefield) != 1)
		p--;
	scanoptionalequals(align);
	int val = scanint(align);
	if (val < 0)
		interror(val, " Bad "+esc("prevgraf"), "I allow only nonnegative values here.", align);
	else
	{
		nest[p].pgfield = val;
		curlist = nest[nestptr];
	}
}
