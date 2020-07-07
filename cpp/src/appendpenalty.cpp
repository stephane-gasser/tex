#include "appendpenalty.h"
#include "lecture.h"
#include "buildpage.h"
#include "newpenalty.h"

void appendpenalty(void)
{
	curval = scanint();
	tail_append(newpenalty(curval));
	if (mode == vmode)
		buildpage();
}
