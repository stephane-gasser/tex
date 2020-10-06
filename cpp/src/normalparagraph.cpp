#include "normalparagraph.h"
#include "equivalent.h"

void normalparagraph(void)
{
	if (looseness())
		eqtb_int[looseness_code].word_define(noPrefix, 0);
	if (hang_indent())
		eqtb_dimen[hang_indent_code].word_define(noPrefix, 0);
	if (hang_after() != 1)
		eqtb_int[hang_after_code].word_define(noPrefix, 1);
	if (par_shape_ptr())
		eqtb_local[par_shape_loc-local_base].define(noPrefix, shape_ref, nullptr);
}
