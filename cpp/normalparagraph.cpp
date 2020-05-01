#include "normalparagraph.h"
#include "eqworddefine.h"
#include "eqdefine.h"

void normalparagraph(void)
{
	if (int_par(looseness_code))
		eqworddefine(5282, 0);
	if (dimen_par(hang_indent_code))
		eqworddefine(5847, 0);
	if (int_par(hang_after_code) != 1)
		eqworddefine(5304, 1);
	if (par_shape_ptr())
		eqdefine(3412, 118, 0);
}
