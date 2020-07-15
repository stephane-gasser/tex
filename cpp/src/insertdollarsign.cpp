#include "insertdollarsign.h"
#include "backinput.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

[[nodiscard]] halfword insertdollarsign(halfword tok)
{
	backinput(tok);
	tok = math_shift_token+'$';
	inserror(tok, "Missing $ inserted", "I've inserted a begin-math/end-math symbol since I think\nyou left one out. Proceed, with fingers crossed.");
	return tok;
}

