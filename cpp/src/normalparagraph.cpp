#include "normalparagraph.h"
#include "equivalent.h"

void normalparagraph(void)
{
	if (looseness())
		word_define(0, &eqtb_int[looseness_code], 0);
	if (hang_indent())
		word_define(0, &eqtb_dimen[hang_indent_code], 0);
	if (hang_after() != 1)
		word_define(0, &eqtb_int[hang_after_code], 1);
	if (par_shape_ptr())
		define(0, &eqtb_local[par_shape_loc-local_base], shape_ref, 0);
}
