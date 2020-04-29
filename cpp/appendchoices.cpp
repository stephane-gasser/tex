#include "appendchoices.h"
#include "pushmath.h"
#include "newchoice.h"
#include "scanleftbrace.h"

void appendchoices(void)
{
	link(curlist.tailfield) = newchoice();
	curlist.tailfield = link(curlist.tailfield);
	savestack[saveptr++].int_ = 0;
	pushmath(13);
	scanleftbrace();
}
