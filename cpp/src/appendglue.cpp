#include "appendglue.h"
#include "lecture.h"
#include "noeud.h"

void appendglue(void)
{
	auto s = curchr;
	switch (s)
	{
		case fil_code: 
			tail_append(newglue(fil_glue));
			break;
		case fill_code: 
			tail_append(newglue(fill_glue));
			break;
		case ss_code: 
			tail_append(newglue(ss_glue));
			break;
		case fil_neg_code: 
			tail_append(newglue(fil_neg_glue));
			break;
		case skip_code: 
			tail_append(newglue(scanglue(glue_val)));
			glue_ref_count(tail)--;
			break;
		case mskip_code: 
			tail_append(newglue(scanglue(mu_val)));
			glue_ref_count(tail)--;
			subtype(tail) = mu_glue;
	}
}
