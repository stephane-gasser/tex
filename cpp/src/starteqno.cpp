#include "starteqno.h"
#include "pushmath.h"
#include "eqworddefine.h"
#include "lecture.h"

void starteqno(Token t)
{
	memoryword m;
	m.int_ = t.chr;
	savestack.push_back(m);
	pushmath(math_shift_group);
	eqworddefine(int_base+cur_fam_code, -1);
	if (every_math())
		begintokenlist(every_math(), every_math_text);
}
