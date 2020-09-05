#include "insertdollarsign.h"
#include "backinput.h"
#include "impression.h"
#include "erreur.h"

[[nodiscard]] Token insertdollarsign(Token t)
{
	backinput(t);
	t.tok = math_shift_token+'$';
	inserror(t, "Missing $ inserted", "I've inserted a begin-math/end-math symbol since I think\nyou left one out. Proceed, with fingers crossed.");
	return t;
}

