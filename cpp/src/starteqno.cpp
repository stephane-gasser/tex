#include "starteqno.h"
#include "pushmath.h"
#include "equivalent.h"
#include "lecture.h"

void starteqno(Token t)
{
	auto m = new MemoryNode(0, 0, t.chr);
	savestack.push_back(m);
	pushmath(math_shift_group);
	eqtb_int[cur_fam_code].word_define(noPrefix, -1);
	if (every_math())
		beginTokenListAboveMacro(every_math(), every_math_text);
}
