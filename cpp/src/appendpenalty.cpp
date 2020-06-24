#include "appendpenalty.h"
#include "scanint.h"
#include "buildpage.h"
#include "newpenalty.h"

void appendpenalty(void)
{
	scanint();
	tail_append(newpenalty(curval));
	if (mode == vmode)
		buildpage();
}
