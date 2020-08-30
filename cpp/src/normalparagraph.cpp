#include "normalparagraph.h"
#include "equivalent.h"

void normalparagraph(void)
{
	if (looseness())
		eqworddefine(&eqtb_int[looseness_code], 0);
	if (hang_indent())
		eqworddefine(&eqtb_dimen[hang_indent_code], 0);
	if (hang_after() != 1)
		eqworddefine(&eqtb_int[hang_after_code], 1);
	if (par_shape_ptr())
		eqdefine(&eqtb_local[par_shape_loc-local_base], shape_ref, 0);
}
