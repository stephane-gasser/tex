#include "saveforafter.h"
#include "overflow.h"

void saveforafter(halfword t)
{
	if (curlevel > 1)
	{
		if (saveptr > maxsavestack)
		{
			maxsavestack = saveptr;
			if (maxsavestack > savesize - 6)
				overflow(541, savesize); //save size
		}
		save_type(saveptr) = 2;
		save_level(saveptr) = 0;
		save_index(saveptr) = t;
		saveptr++;
	}
}
