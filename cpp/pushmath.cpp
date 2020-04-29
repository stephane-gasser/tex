#include "pushmath.h"
#include "pushnest.h"
#include "newsavelevel.h"

void pushmath(groupcode c)
{
	pushnest();
	curlist.modefield = -203;
	curlist.auxfield.int_ = 0;
	newsavelevel(c);
}
