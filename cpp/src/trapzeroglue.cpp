#include "trapzeroglue.h"
#include "deleteglueref.h"

void trapzeroglue(int &val)
{
	if (width(val) == 0 && stretch(val) == 0 && shrink(val) == 0)
	{
		glue_ref_count(zero_glue)++;
		deleteglueref(val);
		val = 0;
	}
}
