#include "trapzeroglue.h"
#include "deleteglueref.h"

GlueSpec *trapzeroglue(GlueSpec *Val)
{
	if (Val->width == 0 && Val->stretch == 0 && Val->shrink == 0)
	{
		zero_glue->glue_ref_count++;
		deleteglueref(Val);
		return nullptr;
	}
	return Val;
}
