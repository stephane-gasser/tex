#include "starteqno.h"
#include "pushmath.h"
#include "eqworddefine.h"
#include "lecture.h"

void starteqno(void)
{
	savestack[saveptr++].int_ = curchr;
	pushmath(15);
	eqworddefine(5307, -1);
	if (every_math())
		begintokenlist(every_math(), 8);
}
