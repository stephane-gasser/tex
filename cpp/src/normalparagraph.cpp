#include "normalparagraph.h"
#include "equivalent.h"

void normalparagraph(void)
{
	if (looseness())
		eqworddefine(int_base+looseness_code, 0);
	if (hang_indent())
		eqworddefine(dimen_base+hang_indent_code, 0);
	if (hang_after() != 1)
		eqworddefine(int_base+hang_after_code, 1);
	if (par_shape_ptr())
		eqdefine(par_shape_loc, shape_ref, 0);
}
