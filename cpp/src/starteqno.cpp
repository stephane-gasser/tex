#include "starteqno.h"
#include "pushmath.h"
#include "eqworddefine.h"
#include "lecture.h"

void starteqno(void)
{
	savestack[saveptr++].int_ = curchr;
	pushmath(math_shift_group);
	eqworddefine(int_base+cur_fam_code, -1);
	if (every_math())
		begintokenlist(every_math(), every_math_text);
}
