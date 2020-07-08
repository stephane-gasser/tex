#include "appendpenalty.h"
#include "lecture.h"
#include "buildpage.h"
#include "noeud.h"

void appendpenalty(void)
{
	tail_append(newpenalty(scanint()));
	if (mode == vmode)
		buildpage();
}
