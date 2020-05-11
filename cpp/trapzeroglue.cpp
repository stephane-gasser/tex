#include "trapzeroglue.h"
#include "deleteglueref.h"

void trapzeroglue(void)
{
	if (width(curval) == 0 && stretch(curval) == 0 && shrink(curval) == 0)
	{
		glue_ref_count(zero_glue)++;
		deleteglueref(curval);
		curval = 0;
	}
}
