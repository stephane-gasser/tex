#include "trapzeroglue.h"
#include "deleteglueref.h"

void trapzeroglue(int &val)
{
	GlueSpec *Val;
	Val->num = val;
	if (Val->width == 0 && Val->stretch == 0 && Val->shrink == 0)
	{
		zero_glue->glue_ref_count++;
		deleteglueref(Val);
		Val = nullptr;
	}
}
