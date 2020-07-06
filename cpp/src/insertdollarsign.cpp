#include "insertdollarsign.h"
#include "backinput.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void insertdollarsign(void)
{
	backinput();
	curtok = math_shift_token+'$';
	inserror("Missing $ inserted", "I've inserted a begin-math/end-math symbol since I think\nyou left one out. Proceed, with fingers crossed.");
}

