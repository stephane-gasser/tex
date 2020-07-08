#include "appendchoices.h"
#include "pushmath.h"
#include "noeud.h"
#include "lecture.h"

void appendchoices(void)
{
	tail_append(newchoice());
	savestack[saveptr++].int_ = 0;
	pushmath(math_choice_group);
	scanleftbrace();
}
