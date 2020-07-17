#include "eqsave.h"
#include "erreur.h"

void eqsave(halfword p, quarterword l)
{
	check_full_save_stack(curalign);
	if (l == level_zero)
		save_type(saveptr) = restore_zero;
	else
	{
		saved(0) = eqtb[p].int_;
		saveptr++;
		save_type(saveptr) = restore_old_value;
	}
	save_level(saveptr) = l;
	save_index(saveptr) = p;
	saveptr++;
}
