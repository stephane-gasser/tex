#include "pushmath.h"
#include "etat.h"
#include "sauvegarde.h"

void pushmath(groupcode c)
{
	pushnest();
	mode = -mmode;
	incompleat_noad = nullptr;
	newsavelevel(c);
}
