#include "pushmath.h"
#include "pushnest.h"
#include "newsavelevel.h"

void pushmath(groupcode c)
{
	pushnest();
	mode = -mmode;
	incompleat_noad = 0;
	newsavelevel(c);
}
