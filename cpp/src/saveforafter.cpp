#include "saveforafter.h"
#include "erreur.h"

void saveforafter(halfword t)
{
	if (curlevel > level_one)
	{
		check_full_save_stack(curalign);
		save_type(saveptr) = insert_token;
		save_level(saveptr) = level_zero;
		save_index(saveptr) = t;
		saveptr++;
	}
}
