#include "pushmath.h"
#include "pushnest.h"
#include "noeud.h"

void pushmath(groupcode c)
{
	pushnest();
	mode = -mmode;
	incompleat_noad = 0;
	newsavelevel(c);
}
