#include "appendchoices.h"
#include "pushmath.h"
#include "newchoice.h"
#include "lecture.h"

void appendchoices(void)
{
	tail_append(newchoice());
	savestack[saveptr++].int_ = 0;
	pushmath(math_choice_group);
	scanleftbrace();
}
