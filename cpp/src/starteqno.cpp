#include "starteqno.h"
#include "pushmath.h"
#include "equivalent.h"
#include "lecture.h"

void starteqno(Token t)
{
	auto m = new MemoryNode;
	m->int_ = t.chr;
	savestack.push_back(m);
	pushmath(math_shift_group);
	eqworddefine(&eqtb_int[cur_fam_code], -1);
	if (every_math())
		begintokenlist(every_math(), every_math_text);
}
