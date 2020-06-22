#include "appendglue.h"
#include "scanglue.h"
#include "newglue.h"

void appendglue(void)
{
	auto s = curchr;
	switch (s)
	{
		case fil_code: 
			curval = fil_glue;
			break;
		case fill_code: 
			curval = fill_glue;
			break;
		case ss_code: 
			curval = ss_glue;
			break;
		case fil_neg_code: 
			curval = fil_neg_glue;
			break;
		case skip_code: 
			scanglue(glue_val);
			break;
		case mskip_code: 
			scanglue(mu_val);
	}
	tail_append(newglue(curval));
	if (s >= skip_code)
	{
		glue_ref_count(curval)--;
		if (s > skip_code)
			subtype(tail) = mu_glue;
	}
}
